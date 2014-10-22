package com.example.s02_04_intent;


import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;


public class MainActivity extends ActionBarActivity {

	private Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        btn=(Button)findViewById(R.id.Button);
        
        OnclickListener listener = new OnclickListener();
        btn.setOnClickListener(listener);
    }

    class OnclickListener implements android.view.View.OnClickListener
    {
    	public void onClick(android.view.View v) 
    	{
    		Intent intent = new Intent();
    		intent.setClass(MainActivity.this, OtherActivity.class);
    		
    		//如提示中那样，最好带上包名
    		intent.putExtra("com.example.s02_04_intent.Age", 20);
    		intent.putExtra("com.example.s02_04_intent.Name", "小明");
    		
    		startActivity(intent);
    	};
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
