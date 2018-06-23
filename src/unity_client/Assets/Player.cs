using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player {
	public int Id{get; set;}
	public string Team{get; set;}
	public int Level{get; set;}
	public List<int> Ressource{get; set;}
	public GameObject Sprite{get; set;}
	public Vector3 PosTile{get; set;}
	public int Orientation{get; set;}
	private Animator animator;

	public Player(int id, GameObject sprite, int orient, string team) {
		Id = id;
		Sprite = sprite;
		animator = sprite.GetComponent<Animator>();
		Team = team;
		Level = 1;
		Ressource = new List<int>();
		for (int i = 0; i < 6; i++)
			Ressource.Add(0);
		Sprite.transform.localScale = new Vector3(7, 7, 7);
		setOrientation(orient);
	}

	public void setPosRot(int X, int Y, int orient) {
		Sprite.transform.position = new Vector3(X * 10 + 5, 0, Y * 10 + 5);
		setOrientation(orient);
	}

	public void setOrientation(int orient) {
		Orientation = orient;
		switch (orient) {
			case 1:
				Sprite.transform.eulerAngles = new Vector3(
				Sprite.transform.eulerAngles.x, 0, Sprite.transform.eulerAngles.z);
				break;
			case 2:
				Sprite.transform.eulerAngles = new Vector3(
				Sprite.transform.eulerAngles.x, 90, Sprite.transform.eulerAngles.z);
				break;
			case 3:
				Sprite.transform.eulerAngles = new Vector3(
				Sprite.transform.eulerAngles.x, 180, Sprite.transform.eulerAngles.z);
				break;
			case 4:
				Sprite.transform.eulerAngles = new Vector3(
				Sprite.transform.eulerAngles.x, 270, Sprite.transform.eulerAngles.z);
				break;
		}
	}

	public void SetQuantity(int ressource, int quantity) {
		Ressource[ressource] = quantity;
	}

	public Vector2 getPos()	{
		return new Vector2((int)(Sprite.transform.position.x / 10), (int)(Sprite.transform.position.y / 10));
	}

	public void setTrigger(string trigger)
	{
		animator.SetTrigger(trigger);
	}

	public void setTrigger(string trigger, bool state)
	{
		animator.SetBool(trigger, state);
	}

	public void setTrigger(string trigger, float value)
	{
		animator.SetFloat(trigger, value < 0.1f ? 0.1f : value);
	}
}
