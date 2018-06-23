using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player {
	public int Id{get; set;}
	public string Team{get; set;}
	public int Level{get; set;}
	public List<int> Ressource{get; set;}
	public GameObject Sprite{get; set;}
	private Vector3 GoalPos;
	private float GoalRot;
	private float GoalSpeed;
	private float GoalRotSpeed;
	public int Orientation{get; set;}
	private Animator animator;

	public Player(int id, GameObject sprite, int orient, string team) {
		Id = id;
		Sprite = sprite;
		animator = sprite.GetComponent<Animator>();
		Team = team;
		Level = 1;
		GoalPos = sprite.transform.position;
		GoalSpeed = 0;
		GoalRotSpeed = 0;
		Ressource = new List<int>();
		for (int i = 0; i < 6; i++)
			Ressource.Add(0);
		Sprite.transform.localScale = new Vector3(7, 7, 7);
		setOrientation(orient);
		GoalRot = getOrientationfromOrient(orient);
	}

	public void setPosRot(int X, int Y, int orient, float time) {
		GoalPos = new Vector3(X * 10 + 5, 0, Y * 10 + 5);
		GoalSpeed = Vector3.Distance(GoalPos, Sprite.transform.position) / time;
		setTrigger("Speed", GoalSpeed);
		Orientation = orient;
		GoalRot = getOrientationfromOrient(orient);
		GoalRotSpeed = Math.Abs(Sprite.transform.rotation.eulerAngles.y - GoalRot) / time;
	}

	public int getOrientationfromOrient(int orient) {
		switch (orient) {
			case 1:
				return (0);
			case 2:
				return (90);
			case 3:
				return (180);
			case 4:
				return (270);
		}
		return (0);
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

	public void moveTowardGoal(float time) {
		if (Sprite.transform.position != GoalPos) {
			Sprite.transform.position = Vector3.MoveTowards(Sprite.transform.position, GoalPos, GoalSpeed * time);
			if (Sprite.transform.position == GoalPos)
				setTrigger ("Speed", 0);
		}
		if (Sprite.transform.rotation.eulerAngles.y != GoalRot)
			Sprite.transform.eulerAngles = new Vector3(Sprite.transform.eulerAngles.x,
				Mathf.MoveTowards(Sprite.transform.eulerAngles.y, GoalRot, GoalRotSpeed * time),
				Sprite.transform.eulerAngles.z);
	}

	public void SetQuantity(int ressource, int quantity) {
		Ressource[ressource] = quantity;
	}

	public Vector2 getPos()	{
		return new Vector2((int)(GoalPos.x / 10), (int)(GoalPos.z / 10));
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
		animator.SetFloat(trigger, value != 0 && value < 0.1f ? 0.1f : value);
	}
}
