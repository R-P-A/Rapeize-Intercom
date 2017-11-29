package com.example.rapeizeintercom;

import android.annotation.TargetApi;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class LoginActivity extends AppCompatActivity {
    Button signInButton;
    EditText userID, password;

    TextView counterText;
    int counter = 5;
    boolean emptySignInField = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        signInButton = (Button) findViewById(R.id.signInButton);
        userID = (EditText) findViewById(R.id.userID);
        password = (EditText) findViewById(R.id.password);

        counterText = (TextView) findViewById(R.id.counterText);
        counterText.setVisibility(View.VISIBLE);
        counterText.setText(Integer.toString(counter));

        signInButton.setOnClickListener(buttonSignInOnClickListener);
    }

    OnClickListener buttonSignInOnClickListener = new OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String userIDTemp, passwordTemp;

            userIDTemp = userID.getText().toString();
            passwordTemp = password.getText().toString();

            String tMsg = "checkin," + userIDTemp + "," + passwordTemp + "\n";

            MyClientTask myClientTask = new MyClientTask(tMsg);

            /**
             * Test for ID/Password empty fields
             */
            if (userIDTemp.equals("")) {
                tMsg = null;
                Toast.makeText(LoginActivity.this, "No User ID entered", Toast.LENGTH_SHORT).show();
                emptySignInField = true;
            } else if (passwordTemp.equals("")) {
                tMsg = null;
                Toast.makeText(LoginActivity.this, "No password entered", Toast.LENGTH_SHORT).show();
                emptySignInField = true;
            }

            if(!emptySignInField) {
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
                while (!myClientTask.getReadDone()) ;
                myClientTask.setReadDone(false);

                /**
                 * Handle the sign in
                 */
                if (myClientTask.getResponse().equals("Checked-in with success,admin")) {
                    counter = 5;
                    counterText.setText(Integer.toString(counter));

                    Toast.makeText(getApplicationContext(), myClientTask.getResponse() + "\nOpening Door" , Toast.LENGTH_SHORT).show();

                    //Start UserActivity.class
                    Intent i = new Intent(LoginActivity.this, AdminActivity.class);
                    String message = userIDTemp + "," + passwordTemp;
                    i.putExtra("msgToActivity", message);
                    startActivity(i);

                } else if (myClientTask.getResponse().equals("Checked-in with success,user")) {
                    counter = 5;
                    counterText.setText(Integer.toString(counter));

                    Toast.makeText(getApplicationContext(), myClientTask.getResponse() + "\nOpening Door" , Toast.LENGTH_SHORT).show();

                    //Start NewActivity.class
                    Intent i = new Intent(LoginActivity.this, UserActivity.class);
                    String message = userIDTemp + "," + passwordTemp;
                    i.putExtra("msgToActivity", message);
                    startActivity(i);

                } else {
                    Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();

                    counter--;
                    counterText.setText(Integer.toString(counter));

                    if (counter == 0) {
                        signInButton.setEnabled(false);
                    }
                }
            } else
                emptySignInField = false;
        }
    };
}