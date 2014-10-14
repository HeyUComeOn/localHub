package com.mitsui0118.s0118;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;


public class MainActivity extends ActionBarActivity {

	private SeekBar seekBar; 
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        seekBar=(SeekBar)findViewById(R.id.SeekBar);
        seekBar.setProgress(0);
        seekBar.setSecondaryProgress(0);
        
        OnSeekBarLis onSeekBarLis =new OnSeekBarLis();
        seekBar.setOnSeekBarChangeListener(onSeekBarLis);
    }

    class OnSeekBarLis implements OnSeekBarChangeListener
    {
    	//fromUser:是否是用户导致的进度变化
    	@Override
    	public void onProgressChanged(SeekBar seekBar, int progress,
    			boolean fromUser) {
    		// TODO Auto-generated method stub
    		System.out.println("progress:"+progress);
    	}
    	
    	@Override
    	public void onStartTrackingTouch(SeekBar seekBar) {
    		// TODO Auto-generated method stub
    		System.out.println("start");
    	}
    	
    	@Override
    	public void onStopTrackingTouch(SeekBar seekBar) {
    		// TODO Auto-generated method stub
    		System.out.println("stop");
    	}
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
