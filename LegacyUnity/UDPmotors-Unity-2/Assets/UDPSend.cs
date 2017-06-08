﻿/*
 
    -----------------------
    UDP-Send
    -----------------------
    // [url]http://msdn.microsoft.com/de-de/library/bb979228.aspx#ID0E3BAC[/url]
   

// todo: shutdown thread at the end
*/

using UnityEngine;
using System.Collections;

using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class UDPSend : MonoBehaviour
{
	private static int localPort;

	// prefs
	private string IP;  // define in init
	public int port;  // define in init

	// "connection" things
	IPEndPoint remoteEndPoint;
	UdpClient client;

	// gui
	public string strMessage="";


	// call it from shell (as program)
	private static void Main()
	{
		UDPSend sendObj=new UDPSend();
		sendObj.init();

		// testing via console
		// sendObj.inputFromConsole();

		// as server sending endless
		sendObj.sendEndless(" endless infos \n");

	}
	// start from unity3d
	public void Start()
	{
		init();
	}

	// OnGUI
	void OnGUI()
	{
		Rect rectObj=new Rect(40,350,200,400);
		GUIStyle style = new GUIStyle();
		style.alignment = TextAnchor.UpperLeft;
		GUI.Box(rectObj,"# Type here data to send via UDP to \n"+ IP + " IP at port " + port + " \n"
			,style);

		// ------------------------
		// send it
		// ------------------------
		strMessage=GUI.TextField(new Rect(40,420,140,20),strMessage);
		if (GUI.Button(new Rect(190,420,40,20),"send"))
		{
			sendString(strMessage+"\n");
		}      
	}

	// init
	public void init()
	{
		// Endpunkt definieren, von dem die Nachrichten gesendet werden.
		print("UDPSend.init()");

		// define
		IP="192.168.43.84";
		port = 8888;

		// ----------------------------
		// Senden
		// ----------------------------
		remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
		client = new UdpClient();

		// status
		print("Sending to "+IP+" : "+port);
		print("Testing: nc -lu "+IP+" : "+port);

	}

	// inputFromConsole
	private void inputFromConsole()
	{
		try
		{
			string text;
			do
			{
				text = Console.ReadLine();

				// Only sends if the message contains text
				if (text != "")
				{
					// We format according to UTF8
					byte[] data = Encoding.UTF8.GetBytes(text);
										// hack to test Arduino control
					// We send to the remote client
					 client.Send(data, data.Length, remoteEndPoint);
				}
			} while (text != "");
		}
		catch (Exception err)
		{
			print(err.ToString());
		}

	}

	// sendData
	public void sendString(string message)
	{
		try
		{
			if (message != "")
			{
			// Change data from binary to characters
			byte[] data = Encoding.UTF8.GetBytes(message);
			// Send it to the remote terminal
			client.Send(data, data.Length, remoteEndPoint);
			}
		}
		catch (Exception err)
		{
			print(err.ToString());
		}
	}


	// endless test
	private void sendEndless(string testStr)
	{
		do
		{
			sendString(testStr);
		}
		while(true);
	}
}