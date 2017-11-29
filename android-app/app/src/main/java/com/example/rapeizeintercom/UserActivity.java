package com.example.rapeizeintercom;

import android.annotation.TargetApi;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class UserActivity extends AppCompatActivity {

    Button buttonCheckOut, buttonOpen;
    String userID, password;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user);


        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] user = message.split(",");
        userID = user[0];
        password = user[1];

        // Locate the buttonCheckOut in activity_user.xml
        buttonCheckOut = (Button) findViewById(R.id.button_check_out);

        buttonCheckOut.setOnClickListener(buttonSignOutOnClickListener);

        // Locate the buttonOpen in activity_main.xml
        buttonOpen = (Button) findViewById(R.id.button_open);

        buttonOpen.setOnClickListener(buttonOpenOnClickListener);
    }

    View.OnClickListener buttonSignOutOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "checkout," + userID + "," + password;

            MyClientTask myClientTask = new MyClientTask(tMsg);

            /**
             * Execute socket
             */
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
                myClientTask.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
            else
                myClientTask.execute();

            /**
             * Wait for server response
             */
            while (!myClientTask.getReadDone());
            myClientTask.setReadDone(false);

            /**
             * Handle the sign out
             */
            if (myClientTask.getResponse().equals("Checked-out with success")) {
                Toast.makeText(getApplicationContext(), myClientTask.getResponse() + "\nOpening Door", Toast.LENGTH_SHORT).show();
                Intent i = new Intent(UserActivity.this, MainActivity.class);
                startActivity(i);
            } else {
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
            }
        }
    };

    View.OnClickListener buttonOpenOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "openDoor," + userID + "," + password;

            MyClientTask myClientTask = new MyClientTask(tMsg);

            /**
             * Execute socket
             */
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
                myClientTask.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
            else
                myClientTask.execute();

            /**
             * Wait for server response
             */
            while (!myClientTask.getReadDone());
            myClientTask.setReadDone(false);

            /**
             * Handle the sign out
             */
            if (myClientTask.getResponse().equals("Checked-out with success"))
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
            else
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
        }
    };
}
