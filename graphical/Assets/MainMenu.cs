using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using TMPro;

public class MainMenu : MonoBehaviour
{
    public TMP_InputField inputField;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void PlayGame()
    {
        if (inputField.text.Length > 0)
        {
            string[] parts = inputField.text.Split(':');
            Settings.serverIP = parts[0];
            Settings.serverPort = int.Parse(parts[1]);
        }
        else
        {
            Settings.serverIP = "127.0.0.1";
            Settings.serverPort = 4242;
        }
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 2);
    }

    public void QuitGame()
    {
        Application.Quit();
    }
}
