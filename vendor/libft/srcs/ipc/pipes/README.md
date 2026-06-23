# Utils for pipes IPC

- Data structures struct pipe_fds
- Creation / teardown
- Robust I/O
- Flags / modes
- dup/redirect
- Multiplexing/waiting
- Process helpers
- using pool manager to clean up on error

# Test part
- unit test for partial writes, EINTR handling nonblock behavior
