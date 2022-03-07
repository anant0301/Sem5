#include "headers.h"

int main(int argc, char const *argv[])
{
	char cmd[MAX_CMD_SIZE];
	char *env[] = {
		"LANG=en_",
		"LOGNAME=anant",
		"LANGUAGE=en_IN:en",
		"MANDATORY_PATH=/usr/share/gconf/ubuntu.mandatory.path",
		"DESKTOP_AUTOSTART_ID=10bb4c55adcf83258316002303258480300000022450007",
		"PWD=/home/anant",
		"DESKTOP_SESSION=ubuntu",
		"DEFAULTS_PATH=/usr/share/gconf/ubuntu.default.path",
		"TERM=xterm-256color",
		"USERNAME=anant",
		"USER=anant",
		"QT_ACCESSIBILITY=1",NULL
	};
	char input_buf[INPUT_BUFFER_SIZE];
	int len;
	pid_t pid;
	FILE *fp = fopen("./log/logfile", "w");
	while(strcmp(cmd, "exit"))
	{
		char cwd[INPUT_BUFFER_SIZE];
		if(getcwd(cwd, INPUT_BUFFER_SIZE) == NULL)
		{
			printf("Current Directory Failure");
		}
		char *arg[MAX_ARG_SIZE];
		printf("%s%s@my_terminal@%s%s$%s%s ", BOLD_ON, KGRN, KBLU, cwd, BOLD_OFF, KWHT);
		fflush(stdout);
		fgets(input_buf, INPUT_BUFFER_SIZE, stdin);
		len = input(input_buf, arg);
		strcpy(cmd, arg[0]);
		fflush(stderr);
		fflush(stdin);
		fflush(stdout);
		while((pid = vfork()) < 0);
		if(strcmp(cmd,"cd") == 0)
		{
			chdir(arg[1]);
		}
		else if(strcmp(cmd, "exit") == 0)
		{
			exit(0);
		}		
		else if(strcmp(cmd, "history") == 0)
		{
			FILE *fp = fopen("/home/anant/Desktop/Anant/Sem 5/Operating Systems/OS Lab/Lab 4/q4/log/logfile", "r");
			char buffer[INPUT_BUFFER_SIZE];
			while(fgets(buffer, INPUT_BUFFER_SIZE, fp) != NULL)
			{
				printf("%s\n", buffer);
				bzero(buffer, INPUT_BUFFER_SIZE);
			}
		}
		else if(pid == 0)
		{
			execvpe(cmd, arg, env);				
		}
		else
		{
			fputs(input_buf, fp);
			wait(NULL);
		}
		fflush(stderr);
		fflush(stdin);
		fflush(stdout);
	}
	fclose(fp);
	return 0;
}
