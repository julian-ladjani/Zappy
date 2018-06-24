using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerSkin : MonoBehaviour {
	public Texture[] textures;
	public int level;
	private int oldLevel = -1;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		Debug.Log("Updating");
		if (level != oldLevel) {
			Debug.Log("Changing Level");
			oldLevel = level;
			Renderer rend = gameObject.GetComponent<Renderer>();
			if (level > 0 && level < 8)
				rend.material.mainTexture = textures[level];
			else
				rend.material.mainTexture = textures[0];
		}
	}

	public void setLevel(int level) {
		this.level = level;
		Debug.Log("Trying to update");
		Update();
	}
}
