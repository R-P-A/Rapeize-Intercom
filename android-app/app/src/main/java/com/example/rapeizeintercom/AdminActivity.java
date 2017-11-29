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

public class AdminActivity extends AppCompatActivity {

    Button buttonAdminSignOut, buttonAdminCreate, buttonAdminUpdate, buttonAdminDelete, buttonAdminRead, buttonAdminOpen;
    String userID, password;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin);

        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] user = message.split(",");
        userID = user[0];
        password = user[1];

        // Locate the buttonCheckOut in activity_main.xml
        buttonAdminSignOut = (Button) findViewById(R.id.buttonAdminSignOut);

        buttonAdminSignOut.setOnClickListener(buttonSignOutOnClickListener);

        // Locate the buttonCheckOut in activity_main.xml
        buttonAdminCreate = (Button) findViewById(R.id.buttonAdminCreate);

        buttonAdminCreate.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(AdminActivity.this, AdminCreateUserActivity.class);
                String message = userID + "," + password;
                i.putExtra("msgToActivity", message);
                startActivity(i);
            }
        });

        // Locate the buttonCheckOut in activity_main.xml
        buttonAdminUpdate = (Button) findViewById(R.id.buttonAdminUpdate);

        buttonAdminUpdate.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(AdminActivity.this, AdminUpdateUserActivity.class);
                String message = userID + "," + password;
                i.putExtra("msgToActivity", message);
                startActivity(i);
            }
        });

//        buttonAdminUpdate.setOnClickListener(buttonUpdateOnClickListener);

        // Locate the buttonCheckOut in activity_main.xml
        buttonAdminDelete = (Button) findViewById(R.id.buttonAdminDelete);

//        buttonAdminDelete.setOnClickListener(buttonDeleteOnClickListener);

        buttonAdminDelete.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(AdminActivity.this, AdminDeleteUserActivity.class);
                String message = userID + "," + password;
                i.putExtra("msgToActivity", message);
                startActivity(i);
            }
        });

        // Locate the buttonCheckOut in activity_main.xml
        buttonAdminRead = (Button) findViewById(R.id.buttonAdminRead);

        buttonAdminRead.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(AdminActivity.this, AdminReadUserActivity.class);
                String message = userID + "," + password;
                i.putExtra("msgToActivity", message);
                startActivity(i);
            }
        });

        // Locate the buttonCheckOut in activity_main.xml
        buttonAdminOpen = (Button) findViewById(R.id.buttonAdminOpen);

        buttonAdminOpen.setOnClickListener(buttonOpenOnClickListener);
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
                Intent i = new Intent(AdminActivity.this, MainActivity.class);
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
