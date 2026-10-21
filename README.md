# Lab 5 - Adam Losser and Parker Adamson

MEASURED DELAY FOR EACH FILE (expected = 100ms)

Activity 1:
- sleep.c: 176 ms
- task_delay.c: 180 ms
- timer.c: 100 ms

Activity 2:
- gpio_interrupt.c: 100ms

Activity 3:
- task_delay.c w/ one extra thread, 1 tick delay: 162 ms
- task_delay.c w/ one extra thread, 100 ms delay: 261 ms
- task_delay.c w/ two extra threads, 1 tick delay: 243 ms
- task_delay.c w/ two extra threads, 100 ms delay: 341 ms

Summary: Using sleep and task delay functions delay the task once it has finished its work, which takes an arbitrary amount of time. This makes it difficult to predict exactly when the next iteration of work will occur. Using interrupts like from a timer or GPIO pin lets you trigger work to happen exactly when you want it to. In activity 3, it appears that when using task delay functions while running multiple tasks only lets you set a minimum amount of time that the delay will occur. When expecting to wait for only 1 tick, the main task ended up waiting hundreds of milliseconds for the scheduler to return to the main thread after performing work on the other threads (for about 80 ms each).

![example workflow](https://github.com/Slcderek/lab0/actions/workflows/main.yml/badge.svg)