OUTPUT_DIR := ./output

BUILD_DIR   := ${OUTPUT_DIR}/build

IMAGE_DIR  := ${OUTPUT_DIR}/image
IMAGE      := ${IMAGE_DIR}/image
IMAGE_SIZE := 256

MOUNT_DIR := ${IMAGE_DIR}/mnt
BOOT_DIR  := ${MOUNT_DIR}/EFI/boot

EFI_BIOS    := /usr/share/ovmf/OVMF.fd
LOOP_DEVICE := /dev/loop0

INCLUDE_DIR := ./include
SOURCE_DIR  := ./source

EFI_PROG_NAME  := image
EFI_PROG_SRC   := ${SOURCE_DIR}/${EFI_PROG_NAME}.asm
EFI_PROG_BUILD := ${BUILD_DIR}/${EFI_PROG_NAME}.efi
EFI_PROG_BOOT  := ${BOOT_DIR}/bootx64.efi

FASM2_DIR     := fasm2
FASM2_C       := ${FASM2_DIR}/fasmg.x64
FASM2_INCLUDE := ${FASM2_DIR}/include;${INCLUDE_DIR}

all: compile copy run

compile: ${FASM2_C} ${BUILD_DIR} ${EFI_PROG_BUILD}

${FASM2_C}:
	git clone https://github.com/tgrysztar/fasm2.git
	chmod +x $(FASM2_C)

${BUILD_DIR}:
	mkdir -p $@

${EFI_PROG_BUILD}: ${EFI_PROG_SRC}
	INCLUDE="${FASM2_INCLUDE}" ${FASM2_C} "-iInclude 'fasm2.inc'" $< $@

copy: compile mount ${EFI_PROG_BOOT}

${EFI_PROG_BOOT}: ${EFI_PROG_BUILD}
	sudo cp ${EFI_PROG_BUILD} $@ && sync

mount: ${IMAGE} ${MOUNT_DIR} ${BOOT_DIR}

${IMAGE}:
	mkdir -p $(dir $@s)
	dd if=/dev/zero of=$@ bs=1MiB count=${IMAGE_SIZE}
	sudo losetup -P ${LOOP_DEVICE} $@
	printf 'g\nn\n\n\n\nt\n1\nw\n' | sudo fdisk ${LOOP_DEVICE} 1> /dev/null
	sudo mkfs.vfat -F32 -I ${LOOP_DEVICE}p1
	sudo losetup -d ${LOOP_DEVICE}
	@sleep 1

${MOUNT_DIR}:
	sudo mkdir -p $@

${BOOT_DIR}:
	sudo losetup -P ${LOOP_DEVICE} ${IMAGE}
	sudo mount ${LOOP_DEVICE}p1 ${MOUNT_DIR}
	sudo mkdir -p $@

unmount:
	sudo umount ${MOUNT_DIR}
	sudo losetup -d ${LOOP_DEVICE}

run: ${EFI_BIOS} ${IMAGE}
	qemu-system-x86_64 -bios ${EFI_BIOS} -drive file=${IMAGE},format=raw -boot c

clean_build:
	rm -r ${BUILD_DIR}

clean_image:
	rm -r ${IMAGE_DIR}

clean_fasm2:
	sudo rm -r ${FASM2_DIR}
