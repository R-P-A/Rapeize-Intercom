package com.example.rapeizeintercom;

import android.os.AsyncTask;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by ruanmolgero on 28/11/17.
 * Android Socket Client
 */

public class MyClientTask extends AsyncTask<Void, Void, Void> {

    String dstAddress;
    int dstPort;
    String response = "";
    String msgToServer;
    boolean readDone = false;

    MyClientTask(String msgTo) {
        dstAddress = "192.168.1.170";
        dstPort = 8888;
        msgToServer = msgTo;
    }

    protected String getResponse() {
        return response;
    }

    protected void setReadDone(boolean readDone) {
        this.readDone = readDone;
    }

    protected boolean getReadDone() {
        return  readDone;
    }

    @Override
    protected Void doInBackground(Void... arg0) {

        Socket socket = null;
        DataOutputStream dataOutputStream = null;
        DataInputStream dataInputStream = null;

        try {
            socket = new Socket(dstAddress, dstPort);
            socket.setSoTimeout(30000);
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            dataInputStream = new DataInputStream(socket.getInputStream());

            /**
             * Send message to server and wait to read response
             */
            dataOutputStream.writeBytes(msgToServer);

            if(msgToServer != "getActiveUsers") {
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                response = in.readLine();
                readDone = true;
            } else {
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                StringBuilder everything = new StringBuilder();

                while( (response = in.readLine()) != null)
                    everything.append(response + "\n");

                response = everything.toString();
                readDone = true;
            }

//            LoginActivity.this.runOnUiThread(new Runnable() {
//
//                @Override
//                public void run() {
//                    Toast.makeText(LoginActivity.this, "MyClientTask ended", Toast.LENGTH_SHORT).show();
//                }
//            });

        } catch (UnknownHostException e) {
            e.printStackTrace();
            response = "UnknownHostException: " + e.toString();
        } catch (IOException e) {
            e.printStackTrace();
            response = "IOException: " + e.toString();
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            if (dataOutputStream != null) {
                try {
                    dataOutputStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            if (dataInputStream != null) {
                try {
                    dataInputStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }

    @Override
    protected void onPostExecute(Void result) {
        //textResponse.setText(response);
        super.onPostExecute(result);
    }

}
