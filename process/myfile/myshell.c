#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>




int main()
{
    for (;;)
    {
        printf("myshell@host:");
        fflush(stdout);

        //解析输入到shell上的字符串 ls   -a -l
        char buffer[1024];
        int read_size = read(1, buffer, sizeof(buffer));
        if (read_size > 0)
        {
            buffer[read_size - 1] = 0;
        }

        char* shell_argv[32] = {NULL};
        int shell_index = 0;
        char* start = buffer;
        while (*start != '\0')
        {
            while (*start != '\0' && isspace(*start))
            {
                *start = '\0';
                start++;
            }
            shell_argv[shell_index++] = start;
            while (*start != '\0' && !isspace(*start))
            {
                start++;
            }
        }

        //创建子进程来exec

        pid_t pid = vfork();

        if (pid < 0)
        {
            printf("vfork failure\n");
            exit(1);
        }
        else if (pid == 0)
        {
            //考虑重定向 > 
            //在字符串数组中找重定向标志

            int i = 0;

            int flag = 0;

            for (; shell_argv[i] != NULL; ++i )
            {
                if (strcmp(">", shell_argv[i]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            int copyFd;

            shell_argv[i] = NULL;


            if (flag)
            {
                if (shell_argv[i+1] == NULL)
                {
                    printf("command error\n");
                    exit(1);
                }

                close(1);

                int fd = open(shell_argv[i+1], O_WRONLY | O_CREAT, 0777);

                copyFd = dup2(1, fd);
            }

            execvp(shell_argv[0], shell_argv);

            //if (flag)
            //{
            //    close(1);
            //    dup2(copyFd, 1);

            //}

            exit(1);
        }
        else //father process
        {
            int status = 0;
            int ret = waitpid(pid, &status, 0);
            if (ret == pid)
            {
                if (WIFEXITED(status))
                {
                   // printf("exitCode is %d\n", WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status))
                {
                    printf("signal is %d\n", WTERMSIG(status));
                }
            }
        }

    }
    return 0;
}
