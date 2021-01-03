#pragma once
#include "FastSpinlock.h"
#include "OverlappedIOContext.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(SOCKET sock, size_t sendBufSize, size_t recvBufSize);
	virtual ~Session() {}

	bool IsConnected() const { return !!mConnected; }

	void Disconnect(DisconnectReason dr);

	bool PreRecv(); ///< zero byte recv for less page-locking
	bool PostRecv();

	bool PostSend(const char* data, size_t len);
	bool FlushSend();

	void SendCompletion(DWORD transferred);
	void RecvCompletion(DWORD transferred);

	bool OnConnect();
	virtual void OnRead(size_t len) {}
	virtual void OnDisconnect(DisconnectReason dr) {}

	template <class PKT_TYPE>
	bool ParsePacket(PKT_TYPE& pkt)
	{
		// TODO: parsePacket 내용 채울 것
		//return mRecvBuffer.Read((char*)&pkt, pkt.mSize);

		return true;
	}

	void	SetSocket(SOCKET sock) { mSocket = sock; }
	SOCKET	GetSocket() const { return mSocket; }

	void EchoBack();

protected:

	SOCKET			mSocket;

	// TODO: flatbuffer 추가할 것

	FastSpinlock	mSendBufferLock;
	int				mSendPendingCount;

	volatile long	mConnected;

	SOCKADDR_IN		mClientAddr;

};
