﻿using System;
using System.Text;
using System.Timers;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Analytics;
using UnityEngine.EventSystems;
using UnityEngine.Networking;

public class GameEvent : MonoBehaviour {

	private delegate void FunctionServer(string[] args);
	private Dictionary<string, FunctionServer> MessageCommand = new Dictionary<string, FunctionServer>();
	private List<GameObject> ItemObject = new List<GameObject>();
	public GameObject prefab;
	public GameObject particlePrefab;
	public bool playing = true;
	private TcpClient socketConnection;
	private string host = "127.0.0.1";
	private int port = 0;
	public Map virtualMap = null;
	private GameObject EggModel;
	private GameObject Character;
	public Color[] colors;
	private List<string> Teams = new List<string>();
	private List<Player> Players = new List<Player>();
	private List<Egg> Eggs = new List<Egg>();
	private int Frequence = 100;
	private float timerppo = 0;
	private float timercheck = 10;
	private Canvas InventaryUI;
	private Canvas End;
	private Text[] InventaryTextUI;
	private Text[] InventaryInfoTextUI;
	private MeshRenderer[] InventaryMeshUI;
	private Single _sliderData;
	private Canvas Option;
	// Use this for initialization
	void Start () {
		ItemObject.Add(GameObject.Find("Mush"));
		ItemObject.Add(GameObject.Find("Rock"));
		ItemObject.Add(GameObject.Find("Straw"));
		ItemObject.Add(GameObject.Find("Log"));
		ItemObject.Add(GameObject.Find("Rice"));
		ItemObject.Add(GameObject.Find("Barrel"));
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
		InventaryUI = GameObject.Find("InventaryUI").GetComponent<Canvas>();
		InventaryTextUI = GameObject.Find("Quantity").GetComponentsInChildren<Text>();
		InventaryInfoTextUI = GameObject.Find("InfoModif").GetComponentsInChildren<Text>();
		InventaryMeshUI = GameObject.Find("Quantity").GetComponentsInChildren<MeshRenderer>();
		End = GameObject.Find("End").GetComponent<Canvas>();
		Option = GameObject.Find("Option").GetComponent<Canvas>();
	}

	public void SliderChangeValue(Single value)
	{
		_sliderData = value;
	}
	
	public void SliderEndDrag(BaseEventData value)
	{
		SendMessageServer("sst "+_sliderData+"\n");
	}

	public void DisplayInventary(GameObject sprite) {
		if (sprite != null) {
			InventaryUI.enabled = true;
			for (int i = 0; i < Players.Count; i++)
				if (Players[i].Sprite == sprite.transform.parent.gameObject) {
					for (int j = 0; j < Players[i].Ressource.Count ; j++)
						InventaryTextUI[j].text = ":  " + Players[i].Ressource[j].ToString();
						InventaryInfoTextUI[0].text = Players[i].Id.ToString();
						InventaryInfoTextUI[1].text = Players[i].Level.ToString();
						InventaryInfoTextUI[2].text = Players[i].Team;
						break;
				}
			for (int i = 0; i < InventaryMeshUI.Length; i++) {
				InventaryMeshUI[i].enabled = true;
			}
		}
		else {
			InventaryUI.enabled = false;
			for (int i = 0; i < InventaryMeshUI.Length; i++) {
				InventaryMeshUI[i].enabled = false;
			}
		}
	}

	public Map GetVMap()
	{
		return virtualMap;
	}

	Player FindPlayer(int id)
	{
		for(int i = 0; i < Players.Count; i++)
			if(Players[i].Id == id) {
				return Players[i];
			}
		GameObject clone = Instantiate(Character) as GameObject;
		clone.transform.position = new Vector3(0, 0, 0);
		Players.Add(new Player(id, clone, 1, "Unknow"));
		return Players[Players.Count];
	}

	void Welcome(string[] args) {
		SendMessageServer("SPECTATOR\n");
		SendMessageServer("msz\n");
		SendMessageServer("tna\n");
		SendMessageServer("sgt\n");
		SendMessageServer("mct\nmct\nmct\n");
	}

	void MapSize(string[] args) {
		if (args.Length == 3) {
			int X = int.Parse(args[1]);
			int Y = int.Parse(args[2]);
			virtualMap = new Map();
			for (int i = 0; i < Y; i++) {
				virtualMap.chunks.Add(new List<Chunk>());
				for(int j = 0; j < X; j++)
					virtualMap.chunks[i].Add(new Chunk());
			}
			for (int i = 0; i < Y; i++)
			{
				for (int idx = 0; idx < X; idx++)
				{
					var test = Instantiate(prefab);
					test.transform.localScale = new Vector3(10f, 1f, 10f);
					test.transform.position = new Vector3(5f + i * 10, -0.5f, 5f + idx * 10);
				}
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
					clone.transform.Translate(new Vector3(Y*10, 0, X*10));
					if (i == 3 || i == 6 || i == 9)
						clone.transform.Rotate(new Vector3(-90, 0, 0));
					virtualMap.chunks[Y][X].Ressource.Add(clone);
				}
			}
			else if(virtualMap.chunks.Count > Y && virtualMap.chunks[Y].Count > X) {
				for (int i = 3; i < 10; i++){
					if (int.Parse(args[i]) != 0) {
						int quantity = int.Parse(args[i]);
						virtualMap.chunks[Y][X].SetQuantity(i-3, quantity);
						if (quantity > 5)
							quantity = 5;
						virtualMap.chunks[Y][X].Ressource[i-3].transform.localScale = new Vector3(2+quantity, 2+quantity, 2+quantity);
					}
					else
						virtualMap.chunks[Y][X].Ressource[i-3].transform.localScale = new Vector3(0, 0, 0);
				}
			}
		}

	}

    void AddTeam(string[] args)
    {
        if (args.Length == 2 && !Teams.Contains(args[1]))
        {
            Teams.Add(args[1]);
        }
    }

	void NewPlayer(string[] args)
	{
        if (args.Length == 7) {
            int Id = int.Parse(args[1].TrimStart('#'));
            int X = int.Parse(args[2]) * 10 + 5;
            int Y = int.Parse(args[3]) * 10 + 5;
			int Orient = int.Parse(args[4]);
			int level = int.Parse(args[5]);
            string Team = args[6];
            GameObject clone = Instantiate(Character) as GameObject;
            clone.transform.position = new Vector3(X, 0, Y);
            AddTeam(new[] {"tna", Team});
            var grandChild = clone.gameObject.transform.GetChild(0).GetChild(0).gameObject;
            Renderer rend = grandChild.GetComponent<Renderer>();
            rend.material.SetColor("_Color",
                colors[Teams.IndexOf(Team) > 0 ? (Teams.IndexOf(Team) % colors.Length) : 0]);
			Player player = new Player(Id, clone, Orient, Team);
			player.changeLevel(level);
            Players.Add(player);
	    	SendMessageServer("pin #"+Players[Players.Count-1].Id+"\nmct\n");
        }
	}

	void PlayerPosition(string[] args) {
		if (args.Length == 5) {
			Vector2 pos = new Vector2(int.Parse(args[2]), int.Parse(args[3]));
			int orient = int.Parse(args[4]);
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			if (TmpPlayer.getPos() != pos || TmpPlayer.Orientation != orient) {
				TmpPlayer.setTrigger("Incantation", false);
				TmpPlayer.setPosRot((int) pos.x, (int) pos.y, orient, 7/Frequence);
			}
		}
	}

	void PlayerLevel(string[] args) {
		if (args.Length == 3) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.changeLevel(int.Parse(args[2]));
		}
	}
	void PlayerInventory(string[] args) {
		Player TmpPlayer = FindPlayer(int.Parse(args[1]));
		for (int j = 4; j < 11; j++){
			TmpPlayer.SetQuantity(j-4, int.Parse(args[j]));
		}
	}

	void Explusion(string[] args) {
		if (args.Length == 2) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.setTrigger("Eject");
		}
	}

	void PlayerMessage(string[] args) {
		if (args.Length >= 2) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.setTrigger("Broadcast");
		}
	}

	void StartIncantation(string[] args) {
		int X = int.Parse(args[1]);
		int Y = int.Parse(args[2]);
			for (int j = 4; j < args.Length; j++){
				Player TmpPlayer = FindPlayer(int.Parse(args[j]));
				TmpPlayer.setTrigger("Incantation", true);
			}
	}

	void EndIncantation(string[] args) {
		if (args.Length == 4) {
			Vector2 pos = new Vector2(int.Parse(args[1]), int.Parse(args[2]));
			string resultat = args[3];
			foreach (Player player in Players) {
				SendMessageServer("plv #" + player.Id + "\n");
				if (player.getPos() == pos)
					player.setTrigger("Incantation", false);
			}
		}
	}

	void LayingEgg(string[] args){
		if (args.Length == 2) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.setTrigger("Egg");
		}
	}

	void DropRessource(string[] args){
		if (args.Length == 3) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.setTrigger("Obj");
			SendMessageServer("pin #" + TmpPlayer.Id + "\nbct "+TmpPlayer.getPos().x+ " "+TmpPlayer.getPos().y+"\n");
		}
	}

	void CollectRessource(string[] args) {
		if (args.Length == 3) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.setTrigger("Obj");
			SendMessageServer("pin #" + TmpPlayer.Id + "\nbct "+TmpPlayer.getPos().x+ " "+TmpPlayer.getPos().y+"\n");
		}
	}

	void PlayerDeath(string[] args) {
		if (args.Length == 2) {
			Player TmpPlayer = FindPlayer(int.Parse(args[1]));
			TmpPlayer.setTrigger("Dead");
			SendMessageServer("bct "+TmpPlayer.getPos().x+ " "+TmpPlayer.getPos().y+"\n");
			GameObject.Destroy(TmpPlayer.Sprite);
			Players.Remove(TmpPlayer);
		}
	}

	void LaidEgg(string[] args) {
		if (args.Length == 5) {
			int Id = int.Parse(args[1]);
			int X = int.Parse(args[3]);
			int Y = int.Parse(args[4]);
			GameObject clone = Instantiate(EggModel) as GameObject;
			clone.transform.position = new Vector3(X*10+5, 1, Y*10+5);
			Eggs.Add(new Egg(Id, clone));
		}
	}

	void HatchEgg(string[] args) {
		if (args.Length == 5) {
			for(int i = 0; i < Eggs.Count; i++)
				if(Eggs[i].Id == int.Parse(args[1])) 
					Debug.Log("Egg "+ Eggs[i].Id + "Hatch");
				}
	}

	void PlayerInEgg(string[] args) {
		EggDeath(args);
	}

	void EggDeath(string[] args) {
		if (args.Length == 2) {
			for(int i = 0; i < Eggs.Count; i++)
				if(Eggs[i].Id == int.Parse(args[1])) {
					GameObject.Destroy(Eggs[i].Sprite);
					Eggs.RemoveAt(i);
				}
		}
	}

	void SetFrequence(string[] args) {
		if (args.Length == 2) {
			Frequence = int.Parse(args[1]);
			foreach (Player player in Players)
				player.setTrigger("Time", 7/Frequence);
			timerppo = 0;
			GameObject.Find("Slider").GetComponent<Slider>().value = Frequence;
			GameObject.Find("Frequence").GetComponent<Text>().text = Frequence.ToString();
		}
	}

	void EndGame(string[] args) {

		if (args.Length == 2) {
			playing = false;
			string  team = args[1];
			foreach (Player player in Players) {
				if (player.Team == team)
					player.setTrigger("Incantation", true);
				else
					player.setTrigger("Dead");
			}
		End.GetComponentInChildren<Text>().text = "The Team Winner is\n\t"+args[1];
		End.enabled = true;
		}
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

//		Debug.Log(args[0]);
        foreach (var cmd in MessageCommand)
        {
            if (cmd.Key.Equals(args[0]))
                cmd.Value.Invoke(args);
        }
    }

    public void TryData(string serverMessage)
    {
        string[] args = serverMessage.Split('\n');
        for (int i = 0; i < args.Length - 1; i++)
        {
//			Debug.Log(args[i] +" "+ i);
            ParseCommand(args[i]);
        }
    }

    public void ListenForData()
    {
        try
        {
            socketConnection = new TcpClient(host, port);
            Byte[] bytes = new Byte[1024];
            while (true)
            {
                // Get a stream object for reading
                using (NetworkStream stream = socketConnection.GetStream())
                {
                	int length;
                    	// Read incomming stream into byte arrary.
                   	while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                    	{
                        	var incommingData = new byte[length];
                        	Array.Copy(bytes, 0, incommingData, 0, length);
                        	// Convert byte array to string message.
                        	string serverMessage = Encoding.ASCII.GetString(incommingData);
							//Debug.Log("server message received as: " + serverMessage);
                        	UnityMainThreadDispatcher.Instance().Enqueue(() => TryData(serverMessage));
                    	}
                }
            }
        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
            UnityMainThreadDispatcher.Instance()
                .Enqueue(() => GameObject.Find("Fail").GetComponent<Canvas>().enabled = true);
        }
    }

    private void SendMessageServer(string clientMessage)
    {

        if (socketConnection == null)
            return;
        try {
//		Debug.Log("Sending message: " + clientMessage);
		// Get a stream object for writing.
		NetworkStream stream = socketConnection.GetStream();
		if (stream.CanWrite) {
			// Convert string message to byte array.
			byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage);
			// Write byte array to socketConnection stream.
			stream.Write(clientMessageAsByteArray, 0, clientMessageAsByteArray.Length);
			//Debug.Log(clientMessage +" :Client sent his message - should be received by server");
		}
		else{
			End.GetComponentInChildren<Text>().text = "Connection Lose";
			End.enabled = true;
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
		float time = Time.deltaTime;
		if (socketConnection == null)
			return;
		timerppo -= time;
		timercheck -= time;
		if (timercheck <= 0.0f){
			SendMessageServer("check\n");
			timercheck = 60;
		}
		foreach (Player player in Players) {
			player.moveTowardGoal(time);
			if (timerppo <= 0.0f)
				SendMessageServer("ppo #" + player.Id + "\n");
		}
		if (timerppo <= 0.0f)
			timerppo = 3.5f/Frequence;
		if (Input.GetMouseButtonDown(0) && Option.enabled == false) {
        	RaycastHit hit;
        	if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out hit)) {
        		Debug.Log("hit :"+ hit.collider.name);
			if (hit.collider.name != "Necromancer")
				virtualMap.DisplayRessource(hit.transform.position.x/10, hit.transform.position.z/10, particlePrefab);
			else
				DisplayInventary(hit.collider.gameObject);
			}
	        else{
				virtualMap.DisplayRessource(-1, 0, null);
				DisplayInventary(null);
			}
		}
	}
}