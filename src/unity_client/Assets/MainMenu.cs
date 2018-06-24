using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;

public class MainMenu : MonoBehaviour {

		private AudioSource musicMain;
		private AudioSource musicConnect;
		private Canvas Connect;
		private Canvas Fail;
		private Canvas Main;
		private string host;
		private int port;
	// Use this for initialization
	private void Start() {
		GameObject obj;
		GameObject obj2;
		GameObject obj3;
		obj = GameObject.Find("Connection");
		obj2 = GameObject.Find("Menu");
		obj3 = GameObject.Find("Fail");
		musicConnect = obj.GetComponent<AudioSource>();
		musicMain = obj2.GetComponent<AudioSource>();
		Connect = obj.GetComponent<Canvas>();
		Fail = obj3.GetComponent<Canvas>();
		Main = obj2.GetComponent<Canvas>();
		Connect.enabled = false;
		Fail.enabled = false;
		Main.enabled = true;
		musicConnect.Stop();
	}

	private void Connection() {
		Connect.enabled = true;
		musicConnect.Play();
		musicMain.Pause();
	}
	// Update is called once per frame
	public void Quit () {
		Application.Quit();
	}
}
