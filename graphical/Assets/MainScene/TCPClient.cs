using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class TCPTestClient {  	
	#region private members 	
	private TcpClient socketConnection; 	
	public Thread clientReceiveThread; 	
	#endregion  	

	private MainScene mainScene;
	/// <summary> 	
	/// Setup socket connection. 	
	/// </summary> 	

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
	/// <summary> 	
	/// Runs in background clientReceiveThread; Listens for incomming data. 	
	/// </summary>     
	public void ListenForData() { 		
		try { 			
			socketConnection = new TcpClient(Settings.serverIP, Settings.serverPort);  			
			Byte[] bytes = new Byte[1024];             
			while (true) { 				
				// Get a stream object for reading 				
				try {
					using (NetworkStream stream = socketConnection.GetStream()) {
						int length; 					
						// Read incomming stream into byte arrary. 					
						while ((length = stream.Read(bytes, 0, bytes.Length)) != 0) { 						
							var incommingData = new byte[length]; 						
							Array.Copy(bytes, 0, incommingData, 0, length); 						
							// Convert byte array to string message. 						
							string serverMessage = Encoding.ASCII.GetString(incommingData); 						
							Debug.Log("server message received as: " + serverMessage);
							if (serverMessage == "WELCOME\n")
							{
								SendMessage("GRAPHIC\n");
							} else {
								HandleMessage(serverMessage);
							}
						} 				
					}
				} catch (Exception e) {
					Debug.Log(e);
					HandleMessage("error\n"); 
				}
			}         
		}         
		catch (SocketException socketException) {             
			Debug.Log("Socket exception: " + socketException);   
			HandleMessage("error\n");    
		}     
	}  	
	/// <summary> 	
	/// Send message to server using socket connection. 	
	/// </summary> 	
	public void SendMessage(string message) {         
		if (socketConnection == null) {             
			return;         
		}  		
		try { 			
			// Get a stream object for writing. 			
			NetworkStream stream = socketConnection.GetStream(); 			
			if (stream.CanWrite) {                 
				// Convert string message to byte array.                 
				byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(message); 				
				// Write byte array to socketConnection stream.    
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