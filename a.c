#include <stdio.h>
#include <getopt.h>
#define FILENAME "/sys/class/backlight/intel_backlight/brightness"

struct option options[] = {
	{"brightness", required_argument, 0, 'b'}
};

int main(int argc, char *argv[]){
	int opt;
	int brightness = 0;
	while((opt = getopt_long(argc, argv, "b:", options, 0)) != -1){
		switch(opt){
			case 'b':
				sscanf(optarg, "%d", &brightness);
				break;
			default:
				printf("Usage: %s [-b --brightness <brightness>]", argv);
				return 0;
		}
	}
	FILE *fp = fopen(FILENAME, "r");
	int a;
	if(!fp){
		printf("error: file don't exist\n");
		return 0;
	}
	fscanf(fp, "%d", &a);
	fclose(fp);
	fp = fopen(FILENAME, "w");
	if(!fp){
		printf("error: cannot open file. did you forget sudo?\n");
		return 0;
	}
	fprintf(fp, "%d", brightness);
	fclose(fp);
	fp = fopen(FILENAME, "w");
	fprintf(fp, "%d", a);
	getchar();
	fclose(fp);
}
