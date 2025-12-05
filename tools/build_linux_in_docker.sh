#!/usr/bin/env bash
set -euo pipefail

IMAGE_NAME=bad-boggle-solver-linux-build

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

docker build -f Dockerfile.linux-build -t "${IMAGE_NAME}" "${ROOT_DIR}"

docker run --rm \
  -v "${ROOT_DIR}":/src \
  -w /src \
  "${IMAGE_NAME}" \
  bash -lc 'cmake -S . -B build-linux -DCMAKE_BUILD_TYPE=RelWithDebInfo && cmake --build build-linux --target BadBoggleSolver_run -j"$(nproc)"'


