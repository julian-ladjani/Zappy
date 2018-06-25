using System;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.Networking;
using System.Text;

public class ConnectMenu : MonoBehaviour {

	private AudioSource musicMain;
	private AudioSource musicConnect;
	private Canvas Connect;
	private Canvas Fail;
	private Canvas Main;
	private Canvas Option;
	private bool isFail = false;
	private string host = "127.0.0.1";
	private int port = 0;
	private Thread clientReceiveThread;
	private bool isGame = false;

	private void Awake() {
	}

	public void Start() {
		GameObject obj;
		GameObject obj2;
		GameObject obj3;
		GameObject obj4;
		obj = GameObject.Find("Connection");
		obj2 = GameObject.Find("Fail");
		obj3 = GameObject.Find("Menu");
		obj4 = GameObject.Find("Option");
		Connect = obj.GetComponent<Canvas>();
		Fail = obj2.GetComponent<Canvas>();
		Main = obj3.GetComponent<Canvas>();
		Option = obj4.GetComponent<Canvas>();
		musicMain = obj3.GetComponent<AudioSource>();
		musicConnect = obj.GetComponent<AudioSource>();
		Option.enabled = false;
	}

	public void HostnameValueChange(string text) {
		host = text;
	}

	public void PortValueChange(string text) {
		port = int.Parse(text);
	}

	public void ConnectingtoServer() {
		Debug.Log(host +"," + port + "\n");
		GameEvent game = GameObject.Find("GameEvent").GetComponent<GameEvent>();
		game.sethost(host, port);
		clientReceiveThread = new Thread (new ThreadStart(game.ListenForData));
		clientReceiveThread.IsBackground = true;
		clientReceiveThread.Start();
		Main.enabled = false;
 		Connect.enabled = false;
		isGame = true;
	}

	public void ConnectBackonClick()
	{
		Connect.enabled = false;
		musicMain.Play();
		musicConnect.Pause();
	}

	public void FailBackonClick()
	{
		Connect.enabled = false;
		isFail = false;
		isGame = false;
		Fail.enabled = false;
		Main.enabled = true;
		musicMain.Play();
		musicConnect.Pause();
	}

	public void DeconnectedonClick()
	{
		Option.enabled = false;
		SceneManager.LoadScene(Application.loadedLevel);
	}

	private void Update() {
		if (isFail && !Fail.enabled){
			Fail.enabled = true;
		}
		if (Input.GetKeyDown(KeyCode.Escape) && isGame) {
			Option.enabled = !Option.enabled;
	}

}
}