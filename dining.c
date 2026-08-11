#include "header.h"

int semaphore_id = -1;

static void philosopher_routine(int number);
static void acquire_fork(int number);
static void release_fork(int number);
static void destroy_semaphores(void);

int main(void)
{
    pid_t process_id;
    int philosopher_count = 0;
    int index;
    union semun semaphore_data;
    unsigned short initial_state[PHILOSOPHER_COUNT];

    semaphore_id = semget(IPC_PRIVATE,
                          PHILOSOPHER_COUNT,
                          IPC_CREAT | IPC_EXCL | 0664);

    if (semaphore_id == -1)
    {
        perror("semget");
        return EXIT_FAILURE;
    }

    for (index = 0; index < PHILOSOPHER_COUNT; index++)
    {
        initial_state[index] = 1;
    }

    semaphore_data.array = initial_state;

    if (semctl(semaphore_id, 0, SETALL, semaphore_data) == -1)
    {
        perror("semctl SETALL");
        destroy_semaphores();
        return EXIT_FAILURE;
    }

    for (index = 0; index < PHILOSOPHER_COUNT; index++)
    {
        process_id = fork();

        if (process_id == -1)
        {
            perror("fork()");
            break;
        }

        if (process_id == 0)
        {
            philosopher_routine(index);
            _exit(EXIT_SUCCESS);
        }

        philosopher_count++;
    }

    for (index = 0; index < philosopher_count; index++)
    {
        wait(NULL);
    }

    destroy_semaphores();

    return EXIT_SUCCESS;
}


static void philosopher_routine(int number)
{
    int meal_number;
    int first_fork = number;
    int second_fork = (number + 1) % PHILOSOPHER_COUNT;

    for (meal_number = 0; meal_number < TOTAL_MEALS; meal_number++)
    {
        printf("Philosopher %d is thinking.\n", number);
        sleep(1);

        printf("Philosopher %d is hungry.\n", number);

        /*
         * Even numbered philosophers acquire the left fork first.
         * Odd numbered philosophers acquire the right fork first.
         * This prevents all philosophers from waiting for the
         * second fork at the same time.
         */
        if ((number & 1) == 0)
        {
            acquire_fork(first_fork);

            printf("Philosopher %d took left fork %d.\n",
                   number, first_fork);

            acquire_fork(second_fork);

            printf("Philosopher %d took right fork %d.\n",
                   number, second_fork);
        }
        else
        {
            acquire_fork(second_fork);

            printf("Philosopher %d took right fork %d.\n",
                   number, second_fork);

            acquire_fork(first_fork);

            printf("Philosopher %d took left fork %d.\n",
                   number, first_fork);
        }

        printf("Philosopher %d is eating.\n\n", number);
        sleep(1);

        release_fork(first_fork);

        printf("Philosopher %d put down forks %d.\n",
               number, first_fork);

        release_fork(second_fork);

        printf("Philosopher %d put down forks %d.\n\n",
               number, second_fork);
    }

    printf("Philosopher %d has finished all meals.\n\n", number);
}


static void acquire_fork(int fork_number)
{
    struct sembuf semaphore_operation;

    semaphore_operation.sem_num = fork_number;
    semaphore_operation.sem_op = -1;
    semaphore_operation.sem_flg = 0;

    if (semop(semaphore_id, &semaphore_operation, 1) == -1)
    {
        perror("semop acquire_fork");
        exit(EXIT_FAILURE);
    }
}


static void release_fork(int fork_number)
{
    struct sembuf semaphore_operation;

    semaphore_operation.sem_num = fork_number;
    semaphore_operation.sem_op = 1;
    semaphore_operation.sem_flg = 0;

    if (semop(semaphore_id, &semaphore_operation, 1) == -1)
    {
        perror("semop release_fork");
        exit(EXIT_FAILURE);
    }
}


static void destroy_semaphores(void)
{
    if (semaphore_id != -1)
    {
        if (semctl(semaphore_id, 0, IPC_RMID) == -1)
        {
            perror("semctl IPC_RMID");
        }

        semaphore_id = -1;
    }
}