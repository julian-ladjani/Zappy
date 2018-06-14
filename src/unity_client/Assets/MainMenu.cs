using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainMenu : MonoBehaviour {

		private AudioSource musicMain;
		private AudioSource musicConnect;
		private Canvas Connect;
	// Use this for initialization
	private void Start() {
		GameObject obj;
		GameObject obj2;
		obj = GameObject.Find("Connection");
		obj2 = GameObject.Find("Menu");
		musicMain = obj.GetComponent<AudioSource>();
		musicConnect = obj2.GetComponent<AudioSource>();
		Connect = obj.GetComponent<Canvas>();
		Connect.enabled = false;
		musicMain.Stop();
	}

	private void Connection() {
		Connect.enabled = true;
		musicMain.Play();
		musicConnect.Stop();
	}
	// Update is called once per frame
	private void Quit () {
		Application.Quit();
	}
}
