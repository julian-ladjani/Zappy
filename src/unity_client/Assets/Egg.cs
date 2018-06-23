using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Egg {
	public int Id;
	public GameObject Sprite{get; set;}

	public Egg(int id, GameObject sprite) {
		Id = id;
		Sprite = sprite;
		Sprite.transform.localScale = new Vector3(1, 1, 1);
	}

}
