using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class Map {

	public List<List<Chunk>> chunks{get; set;}
	public Canvas RessourceUI{get; set;}
	public Text[] TextUI{get;set;}
	public Map() {
		chunks = new List<List<Chunk>>();
		RessourceUI = GameObject.Find("RessourceUI").GetComponent<Canvas>();
		TextUI = GameObject.Find("Ressource").GetComponentsInChildren<Text>();
	}

	public void DisplayRessource(float X, float Y) {
		if(X != -1) {
			RessourceUI.enabled = true;
			for(int i = 0; i < chunks[(int)X][(int)Y].Quantity.Count ; i++){
				TextUI[i].text = chunks[(int)X][(int)Y].Quantity[i].ToString();
			}
		}
		else {
			RessourceUI.enabled = false;
		}
	}
}
