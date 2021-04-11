#!/bin/bash

set -e
echo Creating ISO...

cd "$(dirname "${BASH_SOURCE[0]}")/../.."

# Remove any existing artifacts
rm -rf build

# Create temporary build directories
mkdir -p build/iso/boot/grub
mkdir -p build/output

# Copy required files over
cp tools/boot/grub/grub.cfg build/iso/boot/grub/grub.cfg
cp cmake-build-debug/cosmicOS build/iso/boot/kernel.bin

# Make ISO
if [ $1 = 'docker' ]; then
  docker run -v $(pwd)/build/output:/iso -v $(pwd)/build/iso:/build cosmicos:image grub-mkrescue -o /iso/cosmicOS.iso /build
else
  grub-mkrescue -o build/output/cosmicOS.iso build/iso
fi

# Cleanup
rm -rf build/iso

echo Finished building ISO!