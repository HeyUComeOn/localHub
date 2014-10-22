package com.example.s02_04_intent;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class OtherActivity extends Activity {

	private TextView textview;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.second);
		
		//Return the intent that started this activity.
		Intent intent = getIntent();
		int age=intent.getIntExtra("com.example.s02_04_intent.Age",10);
		String name=intent.getStringExtra("com.example.s02_04_intent.Name");
		
		textview=(TextView)findViewById(R.id.textView1);
		textview.setText(name+age);
	}
	
}
