#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

#include "UnixSocket.hpp"

#define CONNECTION_MAX 3

// UnixSocketServer
UnixSocketServer::~UnixSocketServer()
{
    close();
}

int UnixSocketServer::listen(const char *path)
{
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    /* in case it already exists */
    unlink(path);

    struct sockaddr_un un;
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, path);
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(path);

    int rval;
    /* bind the name to the descriptor */
    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        rval = -2;
    } else {
        if (::listen(fd, CONNECTION_MAX) < 0) {
            rval = -3;
        } else {
            return fd;
        }
    }
    int err = errno;
    close();
    errno = err;

    return rval;
}

int UnixSocketServer::accept(uid_t *uid)
{
    struct sockaddr_un un;
    int len = sizeof(un);
    int clifd = ::accept(fd, (struct sockaddr *)&un, (socklen_t*)&len);
    if (clifd < 0) {
        return -1;
    }

#if 1
    return clifd;
#else

    int rval;
    struct stat statbuf;
    /* obtain the client's uid from its calling address */
    len -= offsetof(struct sockaddr_un, sun_path); /* len of pathname */
    un.sun_path[len] = 0; /* null terminate */
    if (stat(un.sun_path, &statbuf) < 0) {
        rval = -2;
    } else {
        if (S_ISSOCK(statbuf.st_mode)) {
            /* return uid of caller */
            if (uid != NULL) *uid = statbuf.st_uid;
            unlink(un.sun_path); /* we're done with pathname now */
            return clifd;
        } else {
            /* not a socket */
            rval = -3;
        }
    }
    int err = errno;
    ::close(clifd);
    errno = err;

    return rval;
#endif
}

void UnixSocketServer::close()
{
    ::close(fd);
    fd = -1;
}

ssize_t UnixSocketServer::send(const void* buf, size_t size)
{
    return ::send(fd, buf, size, 0);
}

ssize_t UnixSocketServer::recv(int clifd, void* buf, size_t size)
{
    return ::recv(clifd, buf, size, 0);
}

// UnixSocketClient
UnixSocketClient::~UnixSocketClient()
{
    close();
}

int UnixSocketClient::connect(const char *path)
{
    /* create a UNIX domain stream socket */
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    struct sockaddr_un un;

#if 1
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, path);
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(path);
    if (::connect(fd, (struct sockaddr *)&un, len) < 0) {
        return -1;
    } else {
        return fd;
    }
#else

    int rval;

    /* fill socket address structure with our address */
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s-client-%05d", path, getpid());
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    /* in case it already exists */
    unlink(un.sun_path);
    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        rval= -2;
    } else {
        /* fill socket address structure with server's address */
        memset(&un, 0, sizeof(un));
        un.sun_family = AF_UNIX;
        strcpy(un.sun_path, path);
        len = offsetof(struct sockaddr_un, sun_path) + strlen(path);
        if (::connect(fd, (struct sockaddr *)&un, len) < 0) {
            rval = -4;
        } else {
            return fd;
        }
    }

    int err = errno;
    ::close(fd);
    errno = err;

    return rval;

#endif
}

ssize_t UnixSocketClient::send(const void* buf, size_t size)
{
    return ::send(fd, buf, size, 0);
}

ssize_t UnixSocketClient::recv(void* buf, size_t size)
{
    return ::recv(fd, buf, size, 0);
}

void UnixSocketClient::close()
{
    ::close(fd);
    fd = -1;
}
