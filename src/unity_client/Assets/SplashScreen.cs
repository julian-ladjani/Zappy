using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Video;

public class SplashScreen : MonoBehaviour
{
    public bool started = false;
    public VideoPlayer VideoPlayer;

    private void Start()
    {
        VideoPlayer.Play();
        VideoPlayer.loopPointReached += LoadScene;
    }

    void LoadScene(VideoPlayer vp)
    {
        SceneManager.LoadScene("Menu");
    }
}