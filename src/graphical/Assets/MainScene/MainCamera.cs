using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainCamera : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        mainPos = transform.localPosition;
    }
    public float speed = 5.0f;
    private Vector3 mainPos;
    private Vector3 mainAngles;
    // Update is called once per frame
    void Update()
    {
        if (Utils.followTrontorian == null)
        {
            if (transform.localPosition != mainPos)
            {
                transform.localPosition = mainPos;
                transform.localEulerAngles = mainAngles;
            }
            if (Input.GetKey(KeyCode.LeftShift))
                speed = 20.0f;
            else
                speed = 5.0f;
            if (Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D))
            {
                transform.Translate(new Vector3(speed * Time.deltaTime,0,0));
            }
            if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.Q))
            {
                transform.Translate(new Vector3(-speed * Time.deltaTime,0,0));
            }
            if (Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S))
            {
                transform.Translate(new Vector3(0, -speed * Time.deltaTime,0));
            }
            if (Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.Z))
            {
                transform.Translate(new Vector3(0, speed * Time.deltaTime,0));
            }
            if (Input.GetAxis("Mouse ScrollWheel") != 0) {
                Vector3 newValue = transform.localPosition + Vector3.up * Input.GetAxis("Mouse ScrollWheel") * 10;
                if (newValue.y > 1 && newValue.y < 30) {
                    transform.localPosition = newValue;
                }
            }
            mainPos = transform.localPosition;
            mainAngles = transform.localEulerAngles;
        }
        else
        {
            if (Input.GetKey(KeyCode.Escape))
                Utils.followTrontorian = null;
            else
            {
                Vector3 trontorianPos = Utils.followTrontorian.transform.position;
                switch (Utils.followTrontorian.transform.localEulerAngles.y)
                {
                    case 0:
                        transform.localPosition = new Vector3(trontorianPos.x, trontorianPos.y + 1, trontorianPos.z - 2f);
                        break;
                    case 90:
                        transform.localPosition = new Vector3(trontorianPos.x - 2f, trontorianPos.y + 1, trontorianPos.z);
                        break;
                    case 180:
                        transform.localPosition = new Vector3(trontorianPos.x, trontorianPos.y + 1, trontorianPos.z + 2f);
                        break;
                    default:
                        transform.localPosition = new Vector3(trontorianPos.x + 2f, trontorianPos.y + 1, trontorianPos.z);
                        break;
                }
                transform.localEulerAngles = Utils.followTrontorian.transform.localEulerAngles;
            }
        }
    }
}
