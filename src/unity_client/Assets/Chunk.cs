using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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
