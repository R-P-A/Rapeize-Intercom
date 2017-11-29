package com.example.rapeizeintercom;

import android.annotation.TargetApi;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    Button button_check_in, button_list_users;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Get the view from activity_main.xml
        setContentView(R.layout.activity_main);

        // Locate the button_check_in in activity_main.xml
        button_check_in = (Button) findViewById(R.id.button_check_in);

        button_check_in.setOnClickListener(new OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(MainActivity.this, LoginActivity.class);
                startActivity(i);
            }
        });

        // Locate the button_list_users in activity_main.xml
        button_list_users = (Button) findViewById(R.id.button_list_users);

        button_list_users.setOnClickListener(buttonListUsersOnClickListener);
    }

    View.OnClickListener buttonListUsersOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "getActiveUsers";

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

            Intent i = new Intent(MainActivity.this, ListUsersActivity.class);
            String message = myClientTask.getResponse();
            i.putExtra("msgToActivity", message);
            startActivity(i);
        }
    };
}