//
// Created by ivan on 5/22/15.
//

#include <IWCxx/socket/Socket.h>
#include <IWCxx/socket/SocketException.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <IWCxx/socket/Getaddrinfo.h>
// Implementation of the Socket class.





/*
Socket::~Socket() {
    if (is_valid())
        close();
}
*/


/*

ssize_t Socket::send(Bytes bytes) const {
    errno=0;
    ssize_t status = ::send(sockfd_, bytes.data(), bytes.size(), MSG_NOSIGNAL);
    if(status<0)
        throw SocketException(errno,"Socket::send");
    return status != -1;
}


int Socket::recv(std::string &s) const {
    char buf[MAXRECV + 1];

    s = "";

    memset(buf, 0, MAXRECV + 1);

    ssize_t status = ::recv(sockfd_, buf, MAXRECV, 0);

    if (status == -1) {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    } else if (status == 0) {
        return 0;
    } else {
        s = buf;
        return (int) status;
    }
}

void Socket::set_non_blocking(const bool b) {

    int opts;

    opts = fcntl(sockfd_, F_GETFL);

    if (opts < 0) {
        return;
    }

    if (b)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);

    fcntl(sockfd_, F_SETFL, opts);

}*/
Socket  Socket::fill_from_addrinfo(struct addrinfo *obj) {
    int sockfd = Socket::socket(obj->ai_family, obj->ai_socktype, obj->ai_protocol);

    Socket s = Socket(sockfd, SocketAddr(obj->ai_addr, obj->ai_addrlen));
    s.allow_reuse_address();
    return s;
}

Socket  Socket::create(const char * address, std::string port, bool isTCP, int ai_family) {
    Getaddrinfo gai = Getaddrinfo::from_hints(ai_family, isTCP ? SOCK_STREAM : SOCK_DGRAM, AI_PASSIVE);
    gai.run(address, port);

    while (gai.has_next()) {
        struct addrinfo *addrinfo_p = gai.next();
        try {
            return fill_from_addrinfo(addrinfo_p);
        } catch (SocketException &e) {
            continue;
        }
    }

    throw SocketException(-1, "Socket::create");
}

 Socket::~Socket() {
    close();
}

int  Socket::socket(int domain, int type, int protocol) {
    errno = 0;
    int status = ::socket(domain, type, protocol);
    if (status < 0)
        throw SocketException(errno, "Socket::create");
    return status;
}

void Socket::close() const {
    errno = 0;
    int status = ::close(sockfd_);
    if (status < 0)
        throw SocketException(errno, "Socket::close");
}

void Socket::bind() {
    errno = 0;
    int status = ::bind(sockfd_, socket_addr_.sockaddr_ptr(), socket_addr_.saslen());
    if (status < 0)
        throw SocketException(errno, "Socket::bind");
}

void Socket::listen(int backlog) {
    errno = 0;
    int status = ::listen(sockfd_, backlog);
    if (status < 0)
        throw SocketException(errno, "Socket::listen");
}

void Socket::accept(Socket * new_socket, SocketAddr * client) {
    errno = 0;
    struct sockaddr_storage their_addr;
    socklen_t their_size = sizeof(their_addr);

    int status = ::accept(sockfd_, (struct sockaddr *) &their_addr, &their_size);
    if (status < 0)
        throw SocketException(errno, "Socket::accept");

    allow_reuse_address();

    *new_socket = Socket(status);
    *client = SocketAddr(their_addr, their_size));
}

void Socket::connect(const SocketAddr & sadr) const {
    errno = 0;
    int status = ::connect(sockfd_, sadr.sockaddr_ptr(), sadr.saslen());
    if (status < 0)
        throw SocketException(errno, "Socket::connect");
}

ssize_t Socket::send(const Bytes &bytes) const {
    ssize_t status = ::send(sockfd_, bytes.data(), bytes.size(), 0);
    if (status < 0)
        throw SocketException(errno, "Socket::send");
    return status;
}

bool Socket::sendAll(const Bytes &bytes) const {
    size_t offset = 0;
    while (offset != bytes.size()) {
        ssize_t sent = send(Bytes(bytes.begin() + offset, bytes.end()));
        if (sent == 0)
            return false;
        offset += sent;
    }
    return true;
}

ssize_t Socket::send_to(const Bytes &bytes, const SocketAddr &client) const {
    ssize_t status = ::sendto(sockfd_, bytes.data(), bytes.size(), 0, client.sockaddr_ptr(), client.saslen());
    if (status < 0)
        throw SocketException(errno, "Socket::send_to");
    return status;
}

Bytes Socket::recv() const {
    Byte buffer[MAX_BUFFER_SIZE];

    ssize_t status = ::recv(sockfd_, buffer, MAX_BUFFER_SIZE, 0);
    if (status < 0)
        throw SocketException(errno, "Socket::recv");
    return Bytes(buffer, buffer + status);
}

Bytes Socket::recv_from(SocketAddr &client) const {
    Byte buffer[MAX_BUFFER_SIZE];

    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof addr;
    errno = 0;
    ssize_t status = ::recvfrom(sockfd_, buffer, MAX_BUFFER_SIZE-1, 0, (sockaddr *) &addr, &addr_len);
    if (status < 0)
        throw SocketException(errno, "Socket::recv_from");

    client.assign(addr, addr_len);
    return Bytes(buffer, buffer + status);
}

void Socket::allow_reuse_address() {
    int yes = 1;
    int status = setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (status < 0)
        throw SocketException(errno, "Socket::allow_reuse_address");
}

bool Socket::can_read(long max_wait_sec, long max_wait_usec) const {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = max_wait_sec;
    tv.tv_usec = max_wait_usec;

    FD_ZERO(&readfds);
    FD_SET(sockfd(), &readfds);

    // don't care about writefds and exceptfds:
    select(sockfd()+1, &readfds, NULL, NULL, &tv);

    return FD_ISSET(sockfd(), &readfds);
}