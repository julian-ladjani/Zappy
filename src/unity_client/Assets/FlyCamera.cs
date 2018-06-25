using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlyCamera : MonoBehaviour {

	float mainSpeed = 100.0f; //regular speed
	float shiftAdd = 250.0f; //multiplied by how long shift is held.  Basically running
	float maxShift = 1000.0f; //Maximum speed when holdin gshift
    private float totalRun= 1.0f;
	public enum RotationAxes { MouseXAndY = 0, MouseX = 1, MouseY = 2 }
    public RotationAxes axes = RotationAxes.MouseXAndY;
    public float sensitivityX = 15F;
    public float sensitivityY = 15F;
    public float minimumX = -360F;
    public float maximumX = 360F;
    public float minimumY = -60F;
    public float maximumY = 60F;
    public float h = 0;
    float rotationY = 0F;
    Map map = null;
    private Canvas Option;

	void Start ()
	{
		transform.Rotate(h,0,0);
        Option = GameObject.Find("Option").GetComponent<Canvas>();

	}
	void Update () {
        if (Option.enabled)
            return;
        if(Input.GetMouseButton(1))
	    {
	        if (axes == RotationAxes.MouseXAndY)
	        {
	            float rotationX = transform.localEulerAngles.y + Input.GetAxis("Mouse X") * sensitivityX;
	            rotationY += Input.GetAxis("Mouse Y") * sensitivityY;
	            rotationY = Mathf.Clamp (rotationY, minimumY, maximumY);
	            transform.localEulerAngles = new Vector3(-rotationY, rotationX, 0);
	        }
	        else
	        {
	            rotationY += Input.GetAxis("Mouse Y") * sensitivityY;
	            rotationY = Mathf.Clamp (rotationY, minimumY, maximumY);
	            transform.localEulerAngles = new Vector3(-rotationY, transform.localEulerAngles.y, 0);
	        }
	    }

        Vector3 p = GetBaseInput();
        if (Input.GetKey (KeyCode.LeftShift)){
            totalRun += Time.deltaTime;
            p  = p * totalRun * shiftAdd;
            p.x = Mathf.Clamp(p.x, -maxShift, maxShift);
            p.y = Mathf.Clamp(p.y, -maxShift, maxShift);
            p.z = Mathf.Clamp(p.z, -maxShift, maxShift);
        }
        else{
            totalRun = Mathf.Clamp(totalRun * 0.5f, 1f, 1000f);
            p = p * mainSpeed;
        }

        p = p * Time.deltaTime;
       Vector3 newPosition = transform.position;
        if (Input.GetKey(KeyCode.Space)){ //If player wants to move on X and Z axis only
            transform.Translate(p);
            newPosition.x = transform.position.x;
            newPosition.z = transform.position.z;
            transform.position = newPosition;
        }
        else{
            transform.Translate(p);
        }
        LimiteMap();
    }

    private void LimiteMap()
    {
        if ( transform.position.y < 1)
            transform.position = new Vector3(transform.position.x, 1, transform.position.z);
        map = GameObject.Find("GameEvent").GetComponent<GameEvent>().GetVMap();
        if ( transform.position.y > map.chunks.Count*5)
            transform.position = new Vector3(transform.position.x, map.chunks.Count*5, transform.position.z);
        if ( transform.position.z > map.chunks.Count*10)
            transform.position = new Vector3(transform.position.x, transform.position.y, map.chunks.Count*10);
        if ( transform.position.z < -20)
            transform.position = new Vector3(transform.position.x, transform.position.y, -20);
        if ( transform.position.x > map.chunks[0].Count*10)
            transform.position = new Vector3(map.chunks[0].Count*10,transform.position.y, transform.position.z);
        if ( transform.position.x < -20)
            transform.position = new Vector3(-20, transform.position.y, transform.position.z);
    }

    private Vector3 GetBaseInput() { //returns the basic values, if it's 0 than it's not active.
        Vector3 p_Velocity = new Vector3();
        if (Input.GetKey (KeyCode.UpArrow)){
            p_Velocity = new Vector3(0, 0 , 0.1f);
        }
        if (Input.GetKey (KeyCode.DownArrow)){
            p_Velocity = new Vector3(0, 0, -0.1f);
        }
        if (Input.GetKey (KeyCode.LeftArrow)){
            p_Velocity = new Vector3(-0.1f, 0, 0);
        }
        if (Input.GetKey (KeyCode.RightArrow)){
            p_Velocity = new Vector3(0.1f, 0, 0);
        }
        return p_Velocity;
}
}
