using FlatBuffers;
using UnityEngine;
using ZeroMQ;
using FlexBuffers;
using System;

public class Monitor : MonoBehaviour
{
	enum MonitorCommandType
	{
		Test,
		Num,
	};
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
		var bytes = FlexBufferBuilder.Map(root =>
		{
			root.Add("type",(ushort)MonitorCommandType.Test);
			root.Add("content","hello");
		});
		
		requester.Send(new ZFrame(bytes));

		using (ZFrame reply = requester.ReceiveFrame())
		{
			var result=FlxValue.FromBytes(reply.Read()).AsMap;
			var str=result["content"].AsString;
			Debug.Log(str);
		}
	}
}
