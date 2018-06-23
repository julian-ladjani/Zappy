using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GemLevitation : MonoBehaviour
{
    public float MinY = 10f;
    public float MaxY = 20f;
    public float Speed = 0.5f;

    private bool _levitationUp = true;

    // Use this for initialization
    void Start()
    {
        gameObject.transform.position =
            new Vector3(gameObject.transform.position.x, Random.Range(MinY, MaxY), gameObject.transform.position.z);
    }

    // Update is called once per frame
    void Update()
    {
        float y = gameObject.transform.position.y;
        if (_levitationUp)
        {
            y += Speed;
            if (y >= MaxY)
            {
                y = MaxY;
                _levitationUp = false;
            }
        }
        else
        {
            y -= Speed;
            if (y <= MinY)
            {
                y = MinY;
                _levitationUp = true;
            }
        }

        gameObject.transform.position =
            new Vector3(gameObject.transform.position.x, y, gameObject.transform.position.z);
    }
}