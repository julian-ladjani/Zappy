﻿using System;
using System.Text;
using System.Timers;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;
using UnityEngine.Networking;

public class Chunk {
	public List<GameObject> Ressource{get; set;}
	public List<int> Quantity{get;set;}
	public Chunk() {
		Ressource = new List<GameObject>();
		Quantity = new List<int>();
		for (int i = 0; i < 7; i++)
			Quantity.Add(0);
	}
	public void SetQuantity(int ressource, int quantity) {
		Quantity[ressource] = quantity;
	}
}

public class Map {
	public List<List<Chunk>> chunks{get; set;}
	public Map() {
		chunks = new List<List<Chunk>>();
	}
}

public class Player {
	public int Id{get; set;}
	public string Team{get; set;}
	public int Level{get; set;}
	public List<int> Ressource{get; set;}
	public GameObject Sprite{get; set;}
	public Vector3 PosTile{get; set;}

	public Player(int id, GameObject sprite, int orient, string team) {
		Id = id;
		Sprite = sprite;
		Team = team;
		Level = 1;
		Ressource = new List<int>();
		for (int i = 0; i < 6; i++)
			Ressource.Add(0);
		//PosTile = new Vector3(Math.Floor(sprite.transform.position.x),
		//	0, Math.Floor(sprite.transform.position.z));
		setOrientation(orient);
	}

	public void setPosRot(int X, int Y, int orient) {
		Sprite.transform.position = new Vector3(X, 0, Y);
			setOrientation(orient);
	}

	public void setOrientation(int orient) {
		switch (orient) {
			case 1:
				Sprite.transform.rotation = new Quaternion(0, 90, 0, 1);
				break;
			case 2:
				Sprite.transform.rotation = new Quaternion(0, 180, 0, 1);
				break;
			case 3:
				Sprite.transform.rotation = new Quaternion(0, -90, 0, 1);
				break;
			case 4:
				Sprite.transform.rotation = new Quaternion(0, 0, 0, 1);
				break;
		}
	}

	public void SetQuantity(int ressource, int quantity) {
		Ressource[ressource] = quantity;
	}

}

public class Egg {
	public int Id;
	public GameObject Sprite{get; set;}

	public Egg(int id, GameObject sprite) {
		Id = id;
		Sprite = sprite;
	}

}

public class GameEvent : MonoBehaviour {

	private delegate void FunctionServer(string[] args);
	private Dictionary<string, FunctionServer> MessageCommand = new Dictionary<string, FunctionServer>();
	private List<GameObject> ItemObject = new List<GameObject>();
	private TcpClient socketConnection;
	private string host = "127.0.0.1";
	private int port = 0;
	private Terrain map = null;
	private Map virtualMap = null;
	private GameObject EggModel;
	private GameObject Character;
	private List<string> Teams = new List<string>();
	private List<Player> Players = new List<Player>();
	private List<Egg> Eggs = new List<Egg>();
	private int Frequence = -1;
	private float timerppo = -1;
	private int isResource = 0;
	// Use this for initialization
	void Start () {
		ItemObject.Add(GameObject.Find("Mush"));
		ItemObject.Add(GameObject.Find("Rock"));
		ItemObject.Add(GameObject.Find("Straw"));
		ItemObject.Add(GameObject.Find("Log"));
		ItemObject.Add(GameObject.Find("Barrel"));
		ItemObject.Add(GameObject.Find("Rice"));
		ItemObject.Add(GameObject.Find("Diamant"));
		Character = GameObject.Find("Character");
		EggModel = GameObject.Find("Egg");
		MessageCommand["WELCOME"] = new FunctionServer(Welcome);
		MessageCommand["msz"] = new FunctionServer(MapSize);
		MessageCommand["bct"] = new FunctionServer(BaseContent);
		MessageCommand["tna"] = new FunctionServer(AddTeam);
		MessageCommand["pnw"] = new FunctionServer(NewPlayer);
		MessageCommand["ppo"] = new FunctionServer(PlayerPosition);
		MessageCommand["plv"] = new FunctionServer(PlayerLevel);
		MessageCommand["pin"] = new FunctionServer(PlayerInventory);
		MessageCommand["pex"] = new FunctionServer(Explusion);
		MessageCommand["pbc"] = new FunctionServer(PlayerMessage);
		MessageCommand["pic"] = new FunctionServer(StartIncantation);
		MessageCommand["pie"] = new FunctionServer(EndIncantation);
		MessageCommand["pfk"] = new FunctionServer(LayingEgg);
		MessageCommand["pdr"] = new FunctionServer(DropRessource);
		MessageCommand["pgt"] = new FunctionServer(CollectRessource);
		MessageCommand["pdi"] = new FunctionServer(PlayerDeath);
		MessageCommand["enw"] = new FunctionServer(LaidEgg);
		MessageCommand["eht"] = new FunctionServer(HatchEgg);
		MessageCommand["ebo"] = new FunctionServer(PlayerInEgg);
		MessageCommand["edi"] = new FunctionServer(EggDeath);
		MessageCommand["sgt"] = new FunctionServer(SetFrequence);
		MessageCommand["sst"] = new FunctionServer(SetFrequence);
		MessageCommand["seg"] = new FunctionServer(EndGame);
		MessageCommand["smg"] = new FunctionServer(ServerMessage);
		MessageCommand["suc"] = new FunctionServer(UnknowMessage);
		MessageCommand["sbp"] = new FunctionServer(UnknownParameter);
	}

	void Welcome(string[] args) {
		SendMessageServer("SPECTATOR\n");
	}

	void MapSize(string[] args) {
		if (args.Length == 3) {
			int X = int.Parse(args[1]);
			int Y = int.Parse(args[2]);
			if(map == null)
				map = GameObject.Find("Map").GetComponent<Terrain>();
			map.terrainData.size = new Vector3 (X*10, 1, Y*10);
			virtualMap = new Map();
			for (int i = 0; i < Y; i++) {
				virtualMap.chunks.Add(new List<Chunk>());
				for(int j = 0; j < X; j++)
					virtualMap.chunks[i].Add(new Chunk());
			}
		}
	}

	void BaseContent(string[] args) {
		if (args.Length == 10) {
			int X = int.Parse(args[1]);
			int Y = int.Parse(args[2]);
			if (virtualMap.chunks.Count > Y && virtualMap.chunks[Y].Count > X &&
				virtualMap.chunks[Y][X].Ressource.Count == 0) {
				for (int i = 3; i < 10; i++){
					GameObject clone = Instantiate(ItemObject[i-3]) as GameObject;
					clone.transform.Translate(new Vector3(X*10, 0, Y*10));
					if (i == 3 || i == 6 || i == 9)
						clone.transform.Rotate(new Vector3(-90, 0, 0));
					virtualMap.chunks[Y][X].Ressource.Add(clone);
				}
			}
			else if(virtualMap.chunks.Count > Y && virtualMap.chunks[Y].Count > X) {
				for (int i = 3; i < 10; i++){
					if (int.Parse(args[i]) != 0) {
						virtualMap.chunks[Y][X].SetQuantity(i-3, int.Parse(args[i]));
						int quantity = int.Parse(args[i])/3;
						virtualMap.chunks[Y][X].Ressource[i-3].transform.localScale = new Vector3(5+quantity, 5+quantity, 5+quantity);
					}
					else
						virtualMap.chunks[Y][X].Ressource[i-3].transform.localScale = new Vector3(0, 0, 0);
				}
			}
			isResource++;
		}

	}

	void AddTeam(string[] args) {
		if (args.Length == 2) {
			Teams.Add(args[1]);
		}
	}

	void NewPlayer(string[] args){
		if (args.Length == 7) {
			int Id = int.Parse(args[1].TrimStart('#'));
			int X = int.Parse(args[2])*10+5;
			int Y = int.Parse(args[3])*10+5;
			int Orient = int.Parse(args[4]);
			string Team = args[6];
			GameObject clone = Instantiate(Character) as GameObject;
			clone.transform.SetPositionAndRotation(new Vector3(X, 0, Y), transform.rotation);
			Players.Add(new Player(Id, clone, Orient, Team));
		}
	}

	void PlayerPosition(string[] args) {
		if (args.Length == 5) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
					int X = int.Parse(args[2])*10+5;
					int Y = int.Parse(args[3])*10+5;
					int Orient = int.Parse(args[4]);
					Players[i].setPosRot(X, Y, Orient);
					break;
				}
		}
	}

	void PlayerLevel(string[] args) {
		if (args.Length == 3) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
					Players[i].Level = int.Parse(args[2]);
					break;
				}
		}
	}
	void PlayerInventory(string[] args) {
		if (args.Length == 10) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
					for (int j = 3; j < 10; j++) {
						Players[i].SetQuantity(j-3, int.Parse(args[j]));
					break;
				}
			}
		}
	}

	void Explusion(string[] args) {
		if (args.Length == 2) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
				}
		}
	}

	void PlayerMessage(string[] args) {
		if (args.Length == 2) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
				}
		}
	}

	void StartIncantation(string[] args) {
		int X = int.Parse(args[1]);
		int Y = int.Parse(args[2]);
		for(int i = 0; i < Players.Count; i++)
			for(int j = 4; j < args.Length; i++)
				if(Players[i].Id == int.Parse(args[j])) {
				}
	}

	void EndIncantation(string[] args) {
		if (args.Length == 3) {
			int X = int.Parse(args[1]);
			int Y = int.Parse(args[2]);
			string resultat = args[3];
		}
	}

	void LayingEgg(string[] args){
		if (args.Length == 2) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
					Players[i].Ressource[int.Parse(args[2])] -= 1;
				}
		}
	}

	void DropRessource(string[] args){
		if (args.Length == 3) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
					Players[i].Ressource[int.Parse(args[2])] += 1;
				}
		}
	}

	void CollectRessource(string[] args){
		if (args.Length == 3) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
				}
		}
	}

	void PlayerDeath(string[] args){
		if (args.Length == 2) {
			for(int i = 0; i < Players.Count; i++)
				if(Players[i].Id == int.Parse(args[1])) {
					GameObject.Destroy(Players[i].Sprite);
					Players.RemoveAt(i);
				}
		}
	}

	void LaidEgg(string[] args) {
		if (args.Length == 5) {
			int Id = int.Parse(args[1]);
			int X = int.Parse(args[3]);
			int Y = int.Parse(args[4]);
			GameObject clone = Instantiate(EggModel) as GameObject;
			clone.transform.position = new Vector3(X*10, 0, Y*10);
			Eggs.Add(new Egg(Id, clone));
		}
	}

	void HatchEgg(string[] args){
		if (args.Length == 5) {
			for(int i = 0; i < Eggs.Count; i++)
				if(Eggs[i].Id == int.Parse(args[1])) {
				}
		}
	}

	void PlayerInEgg(string[] args){
		if (args.Length == 2) {
			for(int i = 0; i < Eggs.Count; i++)
				if(Eggs[i].Id == int.Parse(args[1])) {
				}
		}
	}

	void EggDeath(string[] args){
		if (args.Length == 2) {
			for(int i = 0; i < Eggs.Count; i++)
				if(Eggs[i].Id == int.Parse(args[1])) {
				}
		}
	}

	void SetFrequence(string[] args) {
		if (args.Length == 2) {
			Frequence = int.Parse(args[1]);
			timerppo = 7/Frequence;
		}
	}

	void EndGame(string[] args) {

	}

	void ServerMessage(string[] args) {
		Debug.Log("Server :" + args[1]);
	}

	void UnknowMessage(string[] args) {
		Debug.Log("Unknow Command");
	}

	void UnknownParameter(string[] args) {
		Debug.Log("Unknow Argument");
	}

	public void ParseCommand(string arg)
	{
		string[] args = arg.Split(' ');
		Debug.Log(args[0]);
		foreach (var cmd in MessageCommand) {
		if (cmd.Key.Equals(args[0]))
			cmd.Value.Invoke(args);
		}
	}

	public void TryData(string serverMessage){
		string[] args = serverMessage.Split('\n');
		for(int i = 0; i < args.Length-1; i++) {
			Debug.Log(args[i] +" "+ i);
			ParseCommand(args[i]);
		}
	}
	public void ListenForData() {
		try {
			socketConnection = new TcpClient(host, port);
			Byte[] bytes = new Byte[1024];
			while (true) {
				// Get a stream object for reading
				using (NetworkStream stream = socketConnection.GetStream()) {
					int length;
					// Read incomming stream into byte arrary.
					while ((length = stream.Read(bytes, 0, bytes.Length)) != 0) {
						var incommingData = new byte[length];
						Array.Copy(bytes, 0, incommingData, 0, length);
						// Convert byte array to string message.
						string serverMessage = Encoding.ASCII.GetString(incommingData);
						Debug.Log("server message received as: " + serverMessage);
						UnityMainThreadDispatcher.Instance().Enqueue(() => TryData(serverMessage));
					}
				}
			}
		}
		catch (SocketException socketException) {
			Debug.Log("Socket exception: " + socketException);
			UnityMainThreadDispatcher.Instance().Enqueue(() => GameObject.Find("Fail").GetComponent<Canvas>().enabled = true);
		}
	}

	private void SendMessageServer(string clientMessage) {
		if (socketConnection == null) {
			return;
		}
		try {
			// Get a stream object for writing.
			NetworkStream stream = socketConnection.GetStream();
			if (stream.CanWrite) {
				// Convert string message to byte array.
				byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage);
				// Write byte array to socketConnection stream.
				stream.Write(clientMessageAsByteArray, 0, clientMessageAsByteArray.Length);
				//Debug.Log(clientMessage +" :Client sent his message - should be received by server");
			}
		}
		catch (SocketException socketException) {
			Debug.Log("Socket exception: " + socketException);
		}
	}

	public void sethost(string host, int port) {
		this.host = host;
		this.port = port;
	}

	void Update () {
		if (socketConnection == null)
			return;
		if (map == null){
			SendMessageServer("msz\n");
		}
		else {
			if (isResource <= 3)
				SendMessageServer("mct\n");
			if (Teams.Count == 0)
				SendMessageServer("tna\n");
			if (Frequence == -1)
				SendMessageServer("sgt\n");
		}
		if (timerppo != -1){
			timerppo -= Time.deltaTime;
			if (timerppo <= 0.0f) {
				for (int i = 0; i < Players.Count; i++)
					SendMessageServer("ppo #"+ Players[i].Id +"\n");
				timerppo = 7/Frequence;
			}
		}

	}
}