{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {self, ...} @ inputs:
    inputs.utils.lib.eachDefaultSystem (
      system: let
        pkgs = import inputs.nixpkgs {inherit system;};
      in rec {
        formatter = pkgs.alejandra;

        devShell = pkgs.mkShell {
          inputsFrom = builtins.attrValues self.packages.${system};
          packages = with pkgs; [clang-tools_18];
        };

        packages = let
          build = type: sanitizer:
            pkgs.stdenv.mkDerivation rec {
              name = "raytracer";
              src = ./.;

              cmakeFlags = [
                "-DCMAKE_BUILD_TYPE=${type}"
                "-DSANITIZER=${sanitizer}"
              ];
              nativeBuildInputs = with pkgs; [cmake libconfig];
              buildInputs = with pkgs; [pkg-config];

              installPhase = ''
                mkdir -p $out/bin
                install -D ${name} $out/bin
              '';

              enableParallelBuilding = true;
            };
        in {
          default = packages.raytracer;
          raytracer = build "Release" "NONE";
          debug = build "Debug" "NONE";
          asan = build "Debug" "MEMORY";
          tsan = build "Debug" "THREAD";
        };
      }
    );
}
