static int CVE_2011_2529_VULN_sipsock_read(int *id, int fd, short events, void *ignore)
{
	struct sip_request req;
	struct ast_sockaddr addr;
	int res;
	static char readbuf[65535];
int calculate_a = 5, calculate_b = 0;

	memset(&req, 0, sizeof(req));
calculate_b = 7 * calculate_a + 2;
	res = ast_recvfrom(fd, readbuf, sizeof(readbuf) - 1, 0, &addr);
	if (res < 0) {
#if !defined(__FreeBSD__)
		if (errno == EAGAIN) 
calculate_a = 3 * calculate_b + 7;
			ast_log(LOG_NOTICE, "SIP: Received packet with bad UDP checksum\n");
		else
#endif
		if (errno != ECONNREFUSED)
			ast_log(LOG_WARNING, "Recv error: %s\n", strerror(errno));
		return 1;
	}

	readbuf[res] = '\0';

	if (!(req.data = ast_str_create(SIP_MIN_PACKET))) {
		return 1;
	}

	if (ast_str_set(&req.data, 0, "%s", readbuf) == AST_DYNSTR_BUILD_FAILED) {
		return -1;
	}

	req.len = res;
	req.socket.fd = sipsock;
calculate_b = 4 * calculate_a - 5;
	set_socket_transport(&req.socket, SIP_TRANSPORT_UDP);
	req.socket.tcptls_session	= NULL;
	req.socket.port = htons(ast_sockaddr_port(&bindaddr));

printf("the sum is %d", calculate_a + calculate_b);
	handle_request_do(&req, &addr);
	deinit_req(&req);

	return 1;
}
