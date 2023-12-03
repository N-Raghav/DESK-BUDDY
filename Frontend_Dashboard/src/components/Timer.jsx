import React, { Component } from 'react';
import './Timer.css';


class Timer extends Component {
  constructor(props) {
    super(props);
    this.state = {
      startTime: null,
      elapsedTime: 0,
      isRunning: false,
      totalTimeElapsed: 0, // New state variable for total elapsed time
    };
  }

  componentDidMount() {
    if (this.state.isRunning) {
      this.startTimer();
    }
  }

  componentWillUnmount() {
    this.stopTimer();
  }

  startTimer = () => {
    this.setState({
      startTime: Date.now() - this.state.elapsedTime,
      isRunning: true,
    });

    this.timerInterval = setInterval(this.updateElapsedTime, 1000);
  };

  stopTimer = () => {
    clearInterval(this.timerInterval);

    if (this.state.isRunning) {
      const newTotalTime = this.state.totalTimeElapsed + this.state.elapsedTime;
      this.setState({
        totalTimeElapsed: newTotalTime,
        isRunning: false,
      });
    }
  };

  resetTimer = () => {
    this.setState({
      startTime: null,
      elapsedTime: 0,
      isRunning: false,
    });
  };

  updateElapsedTime = () => {
    this.setState((prevState) => ({
      elapsedTime: Date.now() - prevState.startTime,
    }));
  };

  render() {
    const { elapsedTime, totalTimeElapsed } = this.state;
  
    const seconds = Math.floor((elapsedTime + totalTimeElapsed) / 1000);
    const minutes = Math.floor(seconds / 60);
    const hours = Math.floor(minutes / 60);
  
    return (
      <div className="TimerContainer">
        <div className="TimerDisplay">
          Elapsed Time: {hours}h {minutes % 60}m {seconds % 60}s
        </div>
        <div className="TotalTime">
          Total Time Elapsed: {Math.floor(totalTimeElapsed / 1000)} seconds
        </div>
        <div className="ButtonContainer">
          <button
            className={`Button ${this.state.isRunning ? 'StopButton' : 'StartButton'}`}
            onClick={this.state.isRunning ? this.stopTimer : this.startTimer}
          >
            {this.state.isRunning ? 'Stop' : 'Start'}
          </button>
          <button className="Button ResetButton" onClick={this.resetTimer}>
            Reset
          </button>
        </div>
      </div>
    );
  }
  
}

export default Timer;
