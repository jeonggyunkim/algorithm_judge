#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

char input_file[100];
char output_file[120];
char code_name[100];

char buf[4097];

int main(int argc, char* argv[]) {
	if (argc != 6) {
		printf("Usage: [이름] [input_file_list] [lang] [MAX_TIME] [MAX_MEMORY]\n");
		exit(0);
	}

	int MAX_TIME = (atoi(argv[4]) * sysconf(_SC_CLK_TCK)) / 1000;
	int MAX_MEMORY = atoi(argv[5]) * 1024;

	sprintf(code_name, "source/%s.%s", argv[1], argv[3]);

	if (argv[3][0] == 'p') {
		fprintf(stderr, "%s\n", argv[1]);
	}
	else {
		fprintf(stderr, "%s\n", argv[1] + 2);
	}

	FILE* in = fopen(argv[2], "rt");
    while (fscanf(in, "%s", input_file) == 1) {
		if (argv[3][0] == 'p') {
			sprintf(output_file, "result/%s/%s_out", argv[1], input_file + 6);
		}
		else {
			sprintf(output_file, "result/%s/%s_out", argv[1] + 2, input_file + 6);
		}
		printf("%s ", input_file);

		int pid;
		if ((pid = fork()) == 0) {
			// child
			int in = open(input_file, O_RDONLY);
			int out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			int err = open("err", O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			dup2(err, STDERR_FILENO);
			close(in);
			close(out);
			close(err);
			if (argv[3][0] == 'p') {
				execlp("pypy3", "pypy3", code_name, NULL);
			}
			else {
				execlp(argv[1], argv[1], NULL);
			}
		}
		else {
			int status, ret;

			char time_info[30];
			char memory_info[30];
			sprintf(time_info, "/proc/%d/stat", pid);
			sprintf(memory_info, "/proc/%d/status", pid);

			unsigned int time_used = 0, memory_used = 0;

			while (1) {
				FILE* f = fopen(time_info, "r");
				if (f) {
					unsigned int utime;

					int read = fscanf(f, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %u", &utime);
					fclose(f);
					if (read == 1) {
						time_used = utime;
					}
				}

				if (time_used > MAX_TIME) {
					kill(pid, SIGKILL);
					ret = waitpid(pid, &status, 0);
					printf("2\n");
					break;
				}

				f = fopen(memory_info, "r");
				if (f) {
					int read = fread(buf, 1, 4095, f);
					buf[read] = '\0';
					fclose(f);

					char* ptr = strstr(buf, "VmPeak:");
					int mem;
					if (ptr) {
						read = sscanf(ptr, "%*s %d", &mem);
						if (read == 1) {
							memory_used = mem;
						}
					}
				}

				if (memory_used > MAX_MEMORY) {
					kill(pid, SIGKILL);
					ret = waitpid(pid, &status, 0);
					printf("3\n");
					break;
				}

				ret = waitpid(pid, &status, WNOHANG);
				if (ret) {
					FILE* err = fopen("err", "rt");
					int errsz = fread(buf, 1, 4096, err);
					buf[errsz] = 0;
					fclose(err);

					if (WIFSIGNALED(status)) {
						int line = 0;
						for (int i = 0; i < errsz; ++i) {
							if (buf[i] == '\n') line++;
						}
						printf("1 %d\n", line + 1);
						fwrite(buf, 1, errsz, stdout);
						putchar('\n');
					}
					else {
						printf("0 %ld %d\n", time_used * (1000 / sysconf(_SC_CLK_TCK)), memory_used);
					}
					break;
				}
			}
		}
		fprintf(stderr, "%s\n", input_file);
	}
	fprintf(stderr, "\n");
	fclose(in);
}
