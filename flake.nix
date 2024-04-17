{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    utils,
    ...
  } @ inputs:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      formatter = pkgs.alejandra;

      devShell = pkgs.mkShell {
        inputsFrom = builtins.attrValues self.packages.${system};

        packages = with pkgs; [
          clang-tools_18
        ];
      };

      packages = rec {
        default = raytracer;
        raytracer = pkgs.stdenv.mkDerivation {
          name = "raytracer";
          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            clang_18
          ];

          installPhase = ''
            mkdir -p $out/bin
            cp raytracer $out/bin
          '';

          enableParallelBuilding = true;
        };
      };
    });
}
