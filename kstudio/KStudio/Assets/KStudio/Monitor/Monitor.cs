using FlatBuffers;
using UnityEngine;
using ZeroMQ;
using FlexBuffers;
using System;

public class Monitor : MonoBehaviour
{
	ZSocket requester;
    void Start()
    {
		requester = new ZSocket(ZSocketType.REQ);
		requester.ReceiveTimeout = new TimeSpan(0,0,10);
		
	}

    [EditorButton]
    void Connect()
    {
		requester.Connect("tcp://127.0.0.1:5555");
	}
    [EditorButton]
	void Test()
    {
		
		var bytes = FlexBufferBuilder.Vector(root =>
		{
			root.Add((ushort)0);
			root.Add("hello");
			
		});
		
		requester.Send(new ZFrame(bytes));

		// Receive
		using (ZFrame reply = requester.ReceiveFrame())
		{
			Debug.Log(" Received: " + reply.ReadString());
		}
	}
}
