{
  description = "Quantum Mechanical Keyboard Firmware";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    qmk-cli-src = { url = "github:qmk/qmk_cli"; flake = false; };
  };

  outputs = { nixpkgs, flake-utils, qmk-cli-src, ... }: flake-utils.lib.eachDefaultSystem (system:
  with nixpkgs.legacyPackages.${system}; let
    qmk-cli = with pkgs.python3Packages; buildPythonApplication rec {
      name = "qmk-cli";
      src = qmk-cli-src;
      propagatedBuildInputs = [
        dotty-dict
        flake8
        hjson
        jsonschema
        milc
        nose2
        setuptools-scm
        pygments
        yapf
      ];

      doCheck = false;
    };

    avrlibc = pkgsCross.avr.libcCross;

    avr_incflags = [
      "-isystem ${avrlibc}/avr/include"
      "-B${avrlibc}/avr/lib/avr5"
      "-L${avrlibc}/avr/lib/avr5"
      "-B${avrlibc}/avr/lib/avr35"
      "-L${avrlibc}/avr/lib/avr35"
      "-B${avrlibc}/avr/lib/avr51"
      "-L${avrlibc}/avr/lib/avr51"
    ];
  in {
    devShell = mkShell {
      name = "qmk-firmware";

      buildInputs = [
        clang-tools
        dfu-programmer
        dfu-util
        diffutils
        git
        qmk-cli
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

      AVR_CFLAGS = avr_incflags;
      AVR_ASFLAGS = avr_incflags;
      shellHook = ''
        # Prevent the avr-gcc wrapper from picking up host GCC flags
        # like -iframework, which is problematic on Darwin
        unset NIX_CFLAGS_COMPILE_FOR_TARGET
      '';

    };
  });
}
