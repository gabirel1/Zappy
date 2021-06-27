using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class TCPTestClient {

	private TcpClient socketConnection; 	
	public Thread clientReceiveThread; 	

	private MainScene mainScene;

	public TCPTestClient(MainScene mainScene)
	{
		this.mainScene = mainScene;	
	}
	public void ConnectToTcpServer () {
		try {
			clientReceiveThread = new Thread (new ThreadStart(ListenForData)); 			
			clientReceiveThread.IsBackground = true; 			
			clientReceiveThread.Start();
		} 		
		catch (Exception e) {
			Debug.Log("On client connect exception " + e); 	
		} 	
	}

	public void ListenForData()
	{
		try
		{
			socketConnection = new TcpClient(Settings.serverIP, Settings.serverPort);
			Byte[] bytes = new Byte[1024];
			while (true)
			{
				try
				{
					using (NetworkStream stream = socketConnection.GetStream())
					{
						int length;
						while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
						{
							var incommingData = new byte[length];
							Array.Copy(bytes, 0, incommingData, 0, length);
							string serverMessage = Encoding.ASCII.GetString(incommingData);
							//Debug.Log("server message received as: " + serverMessage);
							if (serverMessage == "WELCOME\n")
							{
								SendMessage("GRAPHIC\n");
							}
							else
							{
								HandleMessage(serverMessage);
							}
						}
					}
				}
				catch (Exception e)
				{
					Debug.Log(e);
					HandleMessage("error\n");
				}
			}
		}
		catch (SocketException socketException)
		{
			Debug.Log("Socket exception: " + socketException);
			HandleMessage("error\n");
		}
	}

	public void SendMessage(string message) {         
		if (socketConnection == null) {             
			return;         
		}  		
		try { 			
			NetworkStream stream = socketConnection.GetStream(); 			
			if (stream.CanWrite) {                 
				byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(message); 				
				stream.Write(clientMessageAsByteArray, 0, clientMessageAsByteArray.Length);                 
				// Debug.Log("Client sent " + message);             
			}         
		} 		
		catch (SocketException socketException) {             
			Debug.Log("Socket exception: " + socketException);         
		}     
	}

	private void HandleMessage(string message) {
		string[] lines = message.Split('\n');
		for (int i = 0; i < lines.Length; i++)
		{
			mainScene.stockMessage(lines[i]);
		}
	}
}