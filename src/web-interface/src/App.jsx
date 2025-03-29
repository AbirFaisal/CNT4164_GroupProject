/**
 * @file App.jsx
 * @brief IoT and Sensor Networks project
 * @author Abir Faisal <noreply@fau.edu>
 * @date 2025-02-06
 * @copyright Copyright (c) 2025 Florida Atlantic University/Abir Faisal
 * This software is released under the GNU GPLv3 License, see LICENSE.md
 */
import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'

import { useEffect } from 'react'

function App() {
  const [temperature, setTemperature] = useState(0)
  const [humidity, setHumidity] = useState(0)
  const [temperatureSetting, setTemperatureSetting] = useState(20)
  const [mode, setMode] = useState('heating')

  const fetchData = async () => {
    try {
      // process.env.NODE_TLS_REJECT_UNAUTHORIZED = '0';

      const response = await fetch('10.0.3.19', {
        referrerPolicy: "unsafe-url",
        
      })
      
      console.log('response:', response)


      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`)
      }
      const data = await response.json()
      setTemperature(data.temperature)
      setHumidity(data.humidity)
    } catch (error) {
      console.error('Error fetching data:', error)
    }
  }

  useEffect(() => {
    const interval = setInterval(() => {
      fetchData()
    }, 5000) // fetch data every 5 seconds

    return () => clearInterval(interval)
  }, [])

  const increaseTemperatureSetting = () => {
    setTemperatureSetting(prevSetting => prevSetting + 1)
  }

  const decreaseTemperatureSetting = () => {
    setTemperatureSetting(prevSetting => prevSetting - 1)
  }

  const toggleMode = () => {
    setMode(prevMode => (prevMode === 'heating' ? 'cooling' : 'heating'))
  }

  return (
    <>
      <div className="App">
        <header className="App-header">
          <img src={reactLogo} className="App-logo" alt="logo" />
          <img src={viteLogo} className="App-logo" alt="logo" />
          <h1>Thermostat</h1>
          <p>Current Temperature: {temperature.toFixed(2)} C</p>
          <p>Humidity: {humidity.toFixed(2)} %</p>
          <p>Temperature Setting: {temperatureSetting} C</p>
          <button onClick={decreaseTemperatureSetting}>-</button>
          <button onClick={increaseTemperatureSetting}>+</button>
          <p>Mode: {mode}</p>
          <label>
            <input
              type="checkbox"
              checked={mode === 'cooling'}
              onChange={toggleMode}
            />
            Cooling
          </label>
        </header>
      </div>
    </>
  )
}

export default App
