using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GemRotate : MonoBehaviour
{
    public float Speed = 1f;

    // Use this for initialization
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        float y = gameObject.transform.rotation.y;
        if (y >= 360f)
            y = 0;
        else
            y += Speed;
        gameObject.transform.Rotate(0, y, 0, Space.World);
    }
}