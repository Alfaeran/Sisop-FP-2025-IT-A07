#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define PIPE_NAME "/tmp/namedpipe_a19"
#define BUFFER_SIZE 256
#define LOG_FILE "history.log"

int pipe_fd;
FILE *log_file;

void cleanup(int sig)
{
    printf("\nServer shutting down...\n");
    close(pipe_fd);
    unlink(PIPE_NAME);
    if (log_file)
    {
        fclose(log_file);
    }
    exit(0);
}

void log_message(const char *side, const char *message)
{
    if (log_file)
    {
        fprintf(log_file, "[%s] %s\n", side, message);
        fflush(log_file);
    }
}

int main()
{
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Set up signal handler for graceful shutdown
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    // Open log file
    log_file = fopen(LOG_FILE, "a");
    if (!log_file)
    {
        perror("Failed to open log file");
        exit(1);
    }

    // Remove any existing pipe
    unlink(PIPE_NAME);

    // Create named pipe
    if (mkfifo(PIPE_NAME, 0666) == -1)
    {
        perror("mkfifo failed");
        fclose(log_file);
        exit(1);
    }

    printf("Server: Named pipe created at %s\n", PIPE_NAME);
    printf("Server: Waiting for client connection...\n");

    // Open pipe for reading and writing
    pipe_fd = open(PIPE_NAME, O_RDWR);
    if (pipe_fd == -1)
    {
        perror("Failed to open pipe");
        unlink(PIPE_NAME);
        fclose(log_file);
        exit(1);
    }

    printf("Server: Client connected!\n");
    log_message("SERVER", "Client connected");

    while (1)
    {
        // Read message from client
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_read = read(pipe_fd, buffer, BUFFER_SIZE - 1);

        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';

            // Check for exit command
            if (strcmp(buffer, "exit") == 0)
            {
                printf("Server: Client requested exit\n");
                log_message("SERVER", "Client requested exit");
                break;
            }

            printf("Server received: %s\n", buffer);
            log_message("SERVER-RECEIVED", buffer);

            // Generate response
            printf("Server: Enter response: ");
            fflush(stdout);

            if (fgets(response, BUFFER_SIZE, stdin) != NULL)
            {
                // Remove newline character
                response[strcspn(response, "\n")] = 0;

                // Send response to client
                if (write(pipe_fd, response, strlen(response)) == -1)
                {
                    perror("Failed to write to pipe");
                    break;
                }

                printf("Server sent: %s\n", response);
                log_message("SERVER-SENT", response);
            }
        }
        else if (bytes_read == 0)
        {
            printf("Server: Client disconnected\n");
            log_message("SERVER", "Client disconnected");
            break;
        }
        else
        {
            perror("Failed to read from pipe");
            break;
        }
    }

    cleanup(0);
    return 0;
}
