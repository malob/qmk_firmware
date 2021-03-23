{
  description = "Quantum Mechanical Keyboard Firmware";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    devshell.url = "github:numtide/devshell/";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, devshell, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (
    system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        pythonEnv = pkgs.python3.withPackages (
          p: with p; [
            # requirements.txt
            appdirs
            argcomplete
            colorama
            dotty-dict
            hjson
            jsonschema
            milc
            pygments
            # requirements-dev.txt
            nose2
            flake8
            pep8-naming
            yapf
          ]
        );

        avrlibc = pkgs.pkgsCross.avr.libcCross;

        avr_incflags = pkgs.lib.concatStringsSep " " [
          "-isystem ${avrlibc}/avr/include"
          "-B${avrlibc}/avr/lib/avr5"
          "-L${avrlibc}/avr/lib/avr5"
          "-B${avrlibc}/avr/lib/avr35"
          "-L${avrlibc}/avr/lib/avr35"
          "-B${avrlibc}/avr/lib/avr51"
          "-L${avrlibc}/avr/lib/avr51"
        ];
      in
        {
          devShell = devshell.legacyPackages.${system}.mkShell {
            name = "qmk-firmware";

            commands = [
              {
                help = "Make compile_commands.json for Dactyl Manuform";
                name = "dacman-command-db";
                category = "dactyl manuform";
                command = "qmk compiledb -kb handwired/dactyl_manuform/4x6 -km malob";
              }
              {
                help = "Flash Dactyl Manuform left half";
                name = "dacman-flash-left";
                category = "dactyl manuform";
                command = "qmk flash -kb handwired/dactyl_manuform/4x6 -km malob -bl dfu-split-left";
              }
              {
                help = "Flash Dactyl Manuform right half";
                name = "dacman-flash-right";
                category = "dactyl manuform";
                command = "qmk flash -kb handwired/dactyl_manuform/4x6 -km malob -bl dfu-split-right";
              }
              {
                help = "Make compile_commands.json for Crone";
                name = "crkbd-command-db";
                category = "crone";
                command = "qmk compiledb -kb crkbd/rev1/common -km malob";
              }
              {
                help = "Flash Crone left half";
                name = "crkbd-flash-left";
                category = "crone";
                command = "qmk flash -kb crkbd/rev1/common -km malob -bl dfu-split-left";
              }
              {
                help = "Flash Crone right half";
                name = "crkbd-flash-right";
                category = "crone";
                command = "qmk flash -kb crkbd/rev1/common -km malob -bl dfu-split-right";
              }
            ];

            env = [
              {
                name = "AVR_CFLAGS";
                value = avr_incflags;
              }
              {
                name = "AVR_ASFLAGS";
                value = avr_incflags;
              }
              {
                name = "PATH";
                prefix = "bin";
              }
            ];

            packages = with pkgs; [
              clang-tools
              dfu-programmer
              dfu-util
              diffutils
              git
              pythonEnv
              # ARV
              pkgsCross.avr.buildPackages.binutils
              pkgsCross.avr.buildPackages.gcc8
              avrlibc
              avrdude
              # ARM
              gcc-arm-embedded
              # Teensy
              teensy-loader-cli
            ];
          };
        }
  );
}
