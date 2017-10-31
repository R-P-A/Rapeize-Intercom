package com.example.rapeizeintercom;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button button_check_in, button_check_out, button_list_users, button_open;

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
                Intent i = new Intent(MainActivity.this, ToDoActivity.class);
                startActivity(i);
            }
        });

        // Locate the button_check_in in activity_main.xml
        button_check_out = (Button) findViewById(R.id.button_check_out);

        button_check_out.setOnClickListener(new OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(MainActivity.this, ToDoActivity.class);
                startActivity(i);
            }
        });

        // Locate the button_check_in in activity_main.xml
        button_list_users = (Button) findViewById(R.id.button_list_users);

        button_list_users.setOnClickListener(new OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(MainActivity.this, ToDoActivity.class);
                startActivity(i);
            }
        });

        // Locate the button_check_in in activity_main.xml
        button_open = (Button) findViewById(R.id.button_open);

        button_open.setOnClickListener(new OnClickListener() {
            public void onClick(View arg0) {

                //Start NewActivity.class
                Intent i = new Intent(MainActivity.this, ToDoActivity.class);
                startActivity(i);
            }
        });
    }
}