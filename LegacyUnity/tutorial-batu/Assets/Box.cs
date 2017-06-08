using UnityEngine;
using System.Collections;

public class Box : MonoBehaviour {

	public GameObject sphere;
	Rigidbody rb;
	// Use this for initialization
	void Start () {
		rb = GetComponent<Rigidbody>();
		print (rb.mass);
	}
	
	// Update is called once per frame
	void Update () {
		print (rb.velocity);

		if (Input.GetKey(KeyCode.Space)) {
			sphere.transform.localScale = new Vector3 (sphere.transform.localScale.x +0.1f, sphere.transform.localScale.y, sphere.transform.localScale.z);
		}
	}

}
