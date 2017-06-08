using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UDP_Wrapper : MonoBehaviour {

    
    UDPSend udpSend;
	// Use this for initialization
	void Start () {
        udpSend = GetComponent<UDPSend>();
        
        // Connection checking string.
        // udpSend.sendString("0000");
    }
	
	// Update is called once per frame
	void Update () {

        if (Input.GetKeyDown(KeyCode.UpArrow)){
            udpSend.sendString("14");
        }
        if (Input.GetKeyDown(KeyCode.DownArrow)){
            udpSend.sendString("24");
            print("Sending down");
        }
        if (Input.GetKeyDown(KeyCode.LeftArrow)){
            udpSend.sendString("31");
            print("Sending left");
        }
        if (Input.GetKeyDown(KeyCode.RightArrow)){
            udpSend.sendString("41");
            print("Sending right");
        }

        if (Input.GetKeyUp(KeyCode.UpArrow) || Input.GetKeyUp(KeyCode.DownArrow) || Input.GetKeyUp(KeyCode.LeftArrow) || Input.GetKeyUp(KeyCode.RightArrow))
        {
            udpSend.sendString("0");
        }

    }
}
