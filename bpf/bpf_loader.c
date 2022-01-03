#include <linux/bpf.h>
#include <linux/lirc.h>
#include <linux/input.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <asm/types.h>

int main(int argc, char **argv)
{
	struct bpf_object *obj;
	int ret, progfd;

	ret = bpf_prog_load("bpf_program.o", BPF_PROG_TYPE_STORAGE, &obj, &progfd);
	if (ret) {
		printf("Failed to load bpf program\n");
		exit(1);
	}

	ret = bpf_prog_attach(/*prog_fd=*/progfd, /*target_fd=*/0, BPF_STORAGE, 0);
	if (ret) {
		printf("Failed to attach bpf\n");
		exit(1);
	}

	return 0;
}
