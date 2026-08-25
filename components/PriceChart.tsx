"use client";
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from "recharts";
import { onionForecast } from "@/lib/mockData";

export default function PriceChart(){
  const data = onionForecast.map(d=>({ date: d.date.slice(5), actual: d.price || null, predicted: d.predicted || null }));
  return (
    <div className="bg-white p-4 rounded-xl border h-80">
      <h3 className="font-semibold mb-2">Onion - Pune/Nashik Price Trend & 3-Week Forecast (₹/q)</h3>
      <ResponsiveContainer width="100%" height="90%">
        <LineChart data={data}>
          <CartesianGrid strokeDasharray="3 3" />
          <XAxis dataKey="date" tick={{fontSize:11}} />
          <YAxis domain={[2000,3400]} tick={{fontSize:11}} />
          <Tooltip />
          <Legend />
          <Line type="monotone" dataKey="actual" stroke="#16a34a" strokeWidth={2} dot name="Actual Modal" />
          <Line type="monotone" dataKey="predicted" stroke="#f97316" strokeDasharray="5 5" strokeWidth={2} dot name="AI Forecast" />
        </LineChart>
      </ResponsiveContainer>
      <p className="text-xs text-gray-500 mt-1">Source: Aggregated Agmarknet + eNAM + Buyer bids. Forecast: LSTM on 3yr arrival+price+weather.</p>
    </div>
  );
}
