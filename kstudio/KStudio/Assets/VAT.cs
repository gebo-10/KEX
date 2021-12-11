using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAT : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //Time.deltaTime
        var mesh_render = GetComponent<SkinnedMeshRenderer>();
       // mesh_render.SetBlendShapeWeight(0, 50);
        
        var mesh = mesh_render.sharedMesh;
        var count = mesh.GetBlendShapeFrameCount(0);
        Debug.Log(count);
        Vector3[] dp = new Vector3[mesh.vertexCount];
        Vector3[] dn = new Vector3[mesh.normals.Length];
        Vector3[] dt = new Vector3[mesh.triangles.Length];
        mesh.GetBlendShapeFrameVertices(0, 0, dp, null, null);
        //mesh.blend
        foreach(var v in dp)
        {
            Debug.Log(v.x+" "+v.y+" "+v.z);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
