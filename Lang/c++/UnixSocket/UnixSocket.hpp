#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

class UnixSocketServer {
public:
    virtual ~UnixSocketServer();

    /*
     * Create a server endpoint of a connection.
     * Returns fd if all OK, <0 on error.
     */
    int listen(const char *path);
    int accept(uid_t *uidptr);
    void close();

    ssize_t send(const void*, size_t);
    ssize_t recv(int clifd, void*, size_t);

private:
    int fd = -1;
};

class UnixSocketClient {
public:
    virtual ~UnixSocketClient();

    /*
     * Create a client endpoint and connect to a server.
     * Returns fd if all OK, <0 on error.
     */
    int connect(const char *path);
    void close();

    ssize_t send(const void*, size_t);
    ssize_t recv(void*, size_t);

private:
    int fd = -1;
};
